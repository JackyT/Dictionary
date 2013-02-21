/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年08月08日 18时27分37秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "link.h" 
#include "search.h"
#include "head.h"

#define _PORT_ 8000
#define _BACLOG_ 10
#define BUFFER 4096


void *pthread_handler(void *arc);

static WORD *head = NULL;
int main(int argc, const char *argv[])
{
	int er;
	er = system("clear");	
	if(er != 0){
		perror("clear");	
		exit(1);
	}
	char file_name[] = "doc/dict.txt";
	head = scan_file(file_name,"r",head);

	int listen_socket;
	unsigned short port = _PORT_;
	int baclog = _BACLOG_;
	//traverse_link(head);
	//------------------------------------------------------------------------------------------	
	//1.create socket
	//------------------------------------------------------------------------------------------	
	if((listen_socket = socket(AF_INET,SOCK_STREAM,0)) < 0){
		fprintf(stderr,"create socket failed,%s\n",strerror(errno));
		exit(1);
	}
	fprintf(stdout,"New tcp socket created,fd:%d\n",listen_socket);
	int optval;
	optval = 1;
	setsockopt(listen_socket,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval));

#ifdef SO_REUSEPORT
	optval = 1;
	setsockopt(listen_socket,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval));
#endif
	//------------------------------------------------------------------------------------------	
	//2.bind
	//------------------------------------------------------------------------------------------	
	struct sockaddr_in local_ipv4_address;
	memset(&local_ipv4_address,0,sizeof(local_ipv4_address));
	local_ipv4_address.sin_family = AF_INET;
	local_ipv4_address.sin_port = htons(port);
	inet_pton(AF_INET,argv[1],&local_ipv4_address.sin_addr);

	if(bind(listen_socket,(struct sockaddr *)&local_ipv4_address,sizeof(local_ipv4_address)) < 0){
		fprintf(stderr,"bind to %s:%d failed,%s\n",argv[1],port,strerror(errno));	
		exit(2);
	}
	fprintf(stdout,"bound to %s:%d successed.\n",argv[1],port);

	//------------------------------------------------------------------------------------------	
	//3.listen
	//------------------------------------------------------------------------------------------	
	if(listen(listen_socket,baclog) < 0){
		fprintf(stderr,"listen to %s:%d failed,%s\n",argv[1],port,strerror(errno));	
		exit(3);
	}
	fprintf(stdout,"listen to %s:%d successed.\n",argv[1],port);
	fprintf(stdout,"Waiting for connection...\n");	

	//------------------------------------------------------------------------------------------	
	//4.accept
	//------------------------------------------------------------------------------------------	
	int new_connected_socket;
	struct sockaddr_in peer_ipv4_address;
	socklen_t peer_ipv4_addlen;
	//char peer_ipv4_address_string[] = "ddd.ddd.ddd.ddd";
	peer_ipv4_addlen = sizeof(peer_ipv4_address);

	while(1)
	{
		if((new_connected_socket = accept(listen_socket,(struct sockaddr *)&peer_ipv4_address,&peer_ipv4_addlen)) < 0){
			if(errno == EINTR){
				continue;	
			}
			fprintf(stderr,"Accept failed,%s\n",strerror(errno));
			break;
		}else {
			pthread_t tid;
			pthread_attr_t attr;

			pthread_attr_init(&attr);
			pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
#if 1 
			if(pthread_create(&tid,&attr,pthread_handler,(void *)new_connected_socket) < 0){
				fprintf(stderr,"create pthread failed,%s\n",strerror(errno));		
			}
#endif
			fprintf(stdout,"create new pthread :%d success.\n",getpid());
			pthread_attr_destroy(&attr);	

		}

	}

	close(listen_socket);
	return 0;
}
void *pthread_handler(void *arc)
{
	int new_connected_socket = (int)arc;
	//inet_ntop(AF_INET,&peer_ipv4_address.sin_addr,peer_ipv4_address_string,peer_ipv4_addlen);
	//fprintf(stdout,"accept from %s success.\n",peer_ipv4_address_string);
	char receive[BUFFER];
	char send[BUFFER];
	ssize_t bytes;
	bytes = read(new_connected_socket,receive,BUFFER - 1);
	if(bytes < 0){
		fprintf(stderr,"read from remote failed,%s\n",strerror(errno));
	}
	fprintf(stdout,"Read from remote %d bytes.\n",bytes);
	receive[bytes] = '\0';
	fprintf(stdout,"%s\n",receive);
	WORD *ret = NULL;
	if((ret = word_search(head,receive)) == NULL){
		snprintf(send,BUFFER,"Sorry,not find %s.\n\n",receive);	
	}else{
		snprintf(send,BUFFER,"%s\n",ret->trans);	
	}
	bytes = write(new_connected_socket,send,strlen(send));
	if(bytes < 0){
		fprintf(stderr,"write to remote failed,%s\n",strerror(errno));	
	}
	fprintf(stdout,"Send to remote %d bytes.\n",bytes);
	bytes = write(STDOUT_FILENO,send,strlen(send));
	close(new_connected_socket);

	pthread_exit((void *)0);
	

}

