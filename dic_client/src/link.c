/*
 * =====================================================================================
 *
 *       Filename:  link.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年08月08日 17时48分33秒
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
#include "link.h" 
WORD *scan_file(char *file_name,char *parameter,WORD *head)
{
	FILE *fp = fopen(file_name,parameter);	
	if(fp == NULL){
		perror(file_name);	
		exit(1);
	}
	char ch;
	char word_buf[128];
	char trans_buf[1024];
	int i;
	while(1)
	{
		i = 0;
		if((ch = getc(fp)) == '#')
			;
		else 
			if(ch == EOF)
				break;
		ch = getc(fp);
		while(ch != '\n')
		{
			word_buf[i++] = ch;
			ch = getc(fp);
		}
		word_buf[i] = '\0';
		//printf("word:%s\n",word_buf);
		i = 0;
		ch = getc(fp);
		while(ch != '\n')
		{
			trans_buf[i++] = ch;
			ch = getc(fp);
		}
		trans_buf[i] = '\0';
		trans_process(trans_buf);
		//printf("trans:%s\n",trans_buf);
		head = creat_one_node_to_head(head,word_buf,trans_buf);
	}
	fclose(fp);
	return head;
}
WORD *creat_one_node_to_head(WORD *head,char *word,char *trans)
{
	
	WORD *p = malloc(sizeof(WORD));
	if(p == NULL){
		perror("malloc node");	
		exit(1);
	}
	p->word = malloc(sizeof(char)*(strlen(word)+1));
	if(p == NULL){
		perror("malloc word");	
		exit(1);
	}
	strcpy(p->word,word);
	p->trans = malloc(sizeof(char)*(strlen(trans)+1));
	if(p->trans == NULL){
		perror("malloc trans");	
		exit(1);
	}
	strcpy(p->trans,trans);
	p->next = head;

	return p;
}
void trans_process(char *str)
{
	while(*str != '\0')
	{
		if(*str == '@'){
			*str = '\t';
		}
		str++;
	}
}
void traverse_link(WORD *head)
{
	while(head != NULL)
	{
		printf("%s\n%s\n",head->word,head->trans);	
		head = head->next;
	}
}
#if 0
STU *delete_one_node(STU *head, int num)
{
	if(head == NULL)
	{
		puts("empty.");
		return NULL;
	}

	STU *p = head;

	if(head->num == num)
	{
		head = head->next;
		free(p);
		return head;
	}
	STU *ptr = NULL;
	while(p->next != NULL)
	{
		if(p->next->num == num)
		{
			ptr = p->next;
			p->next = p->next->next;
			free(ptr);
			return head;
		}
		p = p->next;
	}
	puts("Not exist!");

	return head;

}
#endif
void destroy(WORD *head)
{
	WORD *p = NULL;	
	while(head != NULL)
	{
		p = head;	
		head = head->next;
		free(p->word);
		free(p->trans);
		free(p);
	}
}

