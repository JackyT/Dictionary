/*
 * =====================================================================================
 *
 *       Filename:  delete.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年08月09日 13时02分10秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include "delete.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void delete_word(const char *word)

{
	
	FILE *fp = fopen("doc/DELETE_WORD.txt","a+");
	if(fp == NULL){
		perror("DELETE_WORD");	
		exit(1);
	}

	char word_buf[128];	
	int i;
	i = 0;
	while(*word != '\0')
	{
		word_buf[i++] = *word++;
	}
	word_buf[i++] = '\n';
	word_buf[i] = '\0';
	
	fprintf(fp,"%s",word_buf);
	fclose(fp);

	return;

}
#if 1 
DELETE *scan_del_doc(DELETE *deled)
{

	FILE *fp = fopen("doc/DELETE_WORD.txt","r");
	if(fp == NULL){
		perror("DELETE_WORD");	
		exit(1);
	}
	char ch;
	char del_buf[128];
	int i;
	while(1)
	{
		ch = getc(fp);
		if(ch == EOF)
			break;
		i = 0;
		while(ch != '\n')	
		{
			del_buf[i++] = ch;
			ch = getc(fp);
		}

		del_buf[i] = '\0';		
		deled = make_del_node(deled,del_buf);
	}
	fclose(fp);
	return deled;
}
#endif

DELETE *make_del_node(DELETE *deled,char *del)
{
	DELETE *p = malloc(sizeof(DELETE));
	if(p == NULL){
		perror("malloc Delete");	
		exit(1);
	}
	p->del = malloc(sizeof(char)*(strlen(del)+1));
	if(p->del == NULL){
		perror("malloc p->del");	
		exit(1);
	}
	strcpy(p->del,del);
	p->next = deled;
	return p;
}

void free_del_link(DELETE *deled)
{
	DELETE *n;
	while(deled != NULL)
	{
		n = deled;
		deled = deled->next;
		free(n->del);
		free(n);
	}
}
DELETE *del_word_search(DELETE *head,const char *str)
{
	if(head == NULL)
		return NULL;
	DELETE *p = head;
	while(p != NULL)
	{
		if(strcmp(p->del,str) == 0)	
			return p;
		else 
			p = p->next;
	}
	return NULL;
}
