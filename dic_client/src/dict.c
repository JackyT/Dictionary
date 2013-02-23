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
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include "link.h" 
#include "search.h"
#include "add.h"
#include "delete.h"
#include "statistics.h"
#include "sent.h"
#include "head.h"

#define _PORT_ 8000
#define BUFFER 4096



int main(int argc, const char *argv[])
{
	int er;
	er = system("clear");	
	if(er != 0){
		perror("clear");	
		exit(1);
	}
	gate();
	char file_name[] = "doc/dict.txt";
	WORD *head = NULL;
	WORD *n = NULL;
	DELETE *deled_word = NULL;
	Link root = NULL;

	head = scan_file(file_name,"r",head);
	head = scan_file("doc/ADD_WORD.txt","r",head);

	root = scan_root_file(root,"doc/STATISTICS.txt"); 
	//traverse(root);
	//traverse_Link(head);
	while(1)	
	{
		er = system("clear");	
		if(er != 0){
			perror("clear");	
			exit(1);
		}
		print_list();
		switch(menu())
		{
		case 1:
			{
				free_del_link(deled_word);
				deled_word = NULL;
				deled_word = scan_del_doc(deled_word);
				char input_word[128];
				int er = 0;
				do{	
					printf("input the word you want to search(# back to main menu):\n\n");
					input(input_word);	
					er = system("clear");
					if(er != 0){
						perror("clear");
						exit(1);
					}
					if(input_word[0] == '#')
						break;
					if(strlen(input_word) < 1){
						puts("you need to input something.");	
						continue;
					}
					addto_root_file("doc/STATISTICS.txt",input_word);
					root = insert(root,input_word);
					if(del_word_search(deled_word,input_word) != NULL){
						printf("You have deleted!\n");
						printf("You can find it back,if you delete the word in DELETE_WORD.txt\n\n");
					}
					else{	
						n = word_search(head,input_word);
						if(n == NULL)
							printf("Sorry,not find!\n\n");
						else
							printf("\n%s\n%s\n\n",n->word,n->trans);
					}	
				}while(1);
				break;
			}
		case 2:
			{
				char part_word[128];
				int n;
				int er;
				while(1)
				{
					printf("you are using misty search function,input part of one word(from word head):\n");
					puts("# bakc to main menu\n");
					int index = 1;
					input(part_word);
					er = system("clear");
					if(er != 0){
						perror("clear");
						exit(1);
					}
					if(part_word[0] == '#')
						break;
					if(strlen(part_word) < 1){
						puts("you need to input something.");	
						continue;
					}
					n = part_word_proc(part_word);
					WORD *p = head;

					while(p != NULL)
					{
						p = part_word_look(p,part_word,n);
						if(p != NULL){
							printf("\t%-3d\t%s\n",index,p->word);
							index++;

							p = p->next;
						}
					}
					putchar('\n');
					if(index == 1)
						printf("Sorry,not find!\n\n");
				}
				break;	
			}
		case 3:
			{
				char new_word[128];
				char new_trans[1024];
				int er;
				while(1)
				{
					printf("input the new word you want to add(# back to main menu):\n");
					input(new_word);
					if(new_word[0] == '#')
						break;
					if(strlen(new_word) < 1){
						puts("you need to input something.");	
						continue;
					}
					printf("Trans:");
					input(new_trans);
					er = system("clear");
					if(er != 0){
						perror("clear");
						exit(1);
					}
					add_proc(new_word,new_trans);
					head = creat_one_node_to_head(head,new_word,new_trans);
					add_word(new_word,new_trans);
					printf("%s\t%s\n",new_word,new_trans);
					puts("Add word success!\n\n");
				}
				break;
			}
		case 4:
			{
				char del_word[128];
				int er;
				while(1)
				{
					printf("input the word you want to delete(# back to main menu):\n\n");
					input(del_word);
					er = system("clear");
					if(er != 0){
						perror("clear");
						exit(1);
					}
					if(del_word[0] == '#')
						break;
					if(strlen(del_word) < 1){
						puts("you need to input something.");	
						continue;
					}
					delete_word(del_word);
					puts("delete word success!\n\n");
				}
				break;
			}
		case 5:
			{
				printf("\t\t|-------| 4.      statistcs      |-------|\n");
				root = root_sort(root);
				printf("press enter back to main menu..");
				while(getchar() != '\n');
				break;
			}
		case 6:
			{

				char sent[1024];
				int er;
				while(1)
				{
					printf("please input a sentence(# back to main menu):\n");	
					input(sent);
					er = system("clear");
					if(er != 0){
						perror("clear");	
						exit(1);
					}
					if(strlen(sent) < 1){
						puts("you need to input something.");	
						continue;
					}
					if(sent[0] == '#')
						break;
					printf("%s\n",sent);
					sent_proc(sent);
					//printf("%s\n",sent);
					char *ret;
					char *tmp = sent;
					char buf[128];
					WORD *p = NULL;
					while(1)
					{
						ret = strsep(&tmp," ");
						if(ret == NULL)
							break;

						p = word_search(head,ret);
						//p->trans process
						if(p != NULL){
							trans_proc(p->trans,buf);
							printf("%s",buf);
							//printf("%s\n",p->trans);
						}	
					}
					putchar('\n');
					putchar('\n');
				}
				break;
			}
		case 7:
			{
				fprintf(stdout,"Please inter the word you want to search,'#' to quit.\n");
				int require_socket;
				unsigned short port = _PORT_;
				struct sockaddr_in remote_ipv4_socket;
				memset(&remote_ipv4_socket,0,sizeof(remote_ipv4_socket));
				remote_ipv4_socket.sin_family = AF_INET,
				remote_ipv4_socket.sin_port = htons(port);
				inet_pton(AF_INET,argv[1],&remote_ipv4_socket.sin_addr);
				while(1)
				{
					//------------------------------------------------------------------------------------
					//1.create socket
					//------------------------------------------------------------------------------------

					if((require_socket = socket(AF_INET,SOCK_STREAM,0)) < 0){
						fprintf(stderr,"create new tcp socket failed,%s\n",strerror(errno));	
						exit(1);
					}
					//fprintf(stdout,"ctreate new tcp socket :%d successed.\n",require_socket);

					ssize_t bytes;
					char send[BUFFER];
					char receive[BUFFER];
					input(send);
					if(send[0] == '#')
						break;
					//------------------------------------------------------------------------------------
					//2.connect
					//------------------------------------------------------------------------------------

					if((connect(require_socket,(struct sockaddr *)&remote_ipv4_socket,sizeof(remote_ipv4_socket))) < 0){
						fprintf(stderr,"connect to remote service %s:%d failed,%s\n",argv[1],port,strerror(errno));	 
						close(require_socket);
						exit(2);
					}
					//fprintf(stdout,"connect to remote service %s:%d successed.\n",argv[1],port);


					bytes = write(require_socket,send,strlen(send));
					//fprintf(stdout,"%d bytes has been sent successed.\n",bytes);
					bytes = read(require_socket,receive,BUFFER - 1);
					//fprintf(stdout,"%d bytes has been received success,\n",bytes);
					bytes = write(STDOUT_FILENO,receive,bytes);
					putchar('\n');
					close(require_socket);
				}
				break;	
			}
		case 8:
			{
				printf("Please input your new password(16 item limited):\n");
				char newpass[17];
				char pass_commit[17];
				int rec;
				rec = password_input(newpass,sizeof(newpass));
				if(rec != 0){
					printf("Create new password failed.Your password is too long");	
					break;
				}
				printf("Please confirm your password:\n");
				rec = password_input(pass_commit,sizeof(pass_commit));			
				if(rec != 0){
					printf("Create new password failed.");	
					break;
				}
				rec = strcmp(newpass,pass_commit);
				if(rec != 0){
					printf("Confirm failed!");	
					break;
				}
				printf("Create new password successfully");
				FILE *fp = fopen("./doc/password","w+");		
				fwrite(newpass,sizeof(char),strlen(newpass),fp);	
				fclose(fp);
				break;
			}
		case 9:
			{
				help_viewer();
				printf("press enter back to main menu..");
				while(getchar() != '\n');
				break;
			}
		case 10:
			{
				printf("\t\t|-------|        Goodbye!        |-------|\n");
				Link_destroy(root);	
				free_del_link(deled_word);
				destroy(head);
				exit(1);
				break;
			}
		default:
			{
				printf("please input number 1~10\n");
				break;
			}
		}
	}

	return 0;
}
