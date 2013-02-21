/*
 * =====================================================================================
 *
 *       Filename:  search.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年08月09日 10时30分33秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include "link.h"
#include "search.h"
#include <string.h>
WORD *part_word_look(WORD *head,char *str,int size)
{
	WORD *p = head;
	if(p == NULL)
		return NULL;
	while(p != NULL)
	{
		if(strncmp(p->word,str,size) == 0)	
			return p;
		else 
			p = p->next;
	}
	return NULL;
}
WORD *word_search(WORD *head,char *str)
{
	WORD *p;
	p = part_search(head,str[0]);
	if(p == NULL)
		return NULL;
	while(p != NULL)
	{
		if(strcmp(p->word,str) == 0)	
			return p;
		else 
			p = p->next;
	}
	return NULL;
}
WORD *part_search(WORD *head,char ch)
{
	if(head == NULL)
		return NULL;
	while(head != NULL)
	{
		if(head->word[0] == ch)	
			return head;
		else
			head = head->next;
	}
	return NULL;
}
