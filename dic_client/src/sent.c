/*
 * =====================================================================================
 *
 *       Filename:  sent.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年08月10日 09时04分59秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <ctype.h>
#include <stdio.h>
void sent_proc(char *sent)
{
	while(*sent != '\0')
	{
		if(*sent >= 'A' && *sent <= 'Z')
			*sent = *sent + 0x20;
		if(!isalpha(*sent))	
			*sent = ' ';
		sent++;
	}
}
void trans_proc(char *str,char *buf)
{
	int i = 6;
	char *p = str;
	while(i)
	{
		p++;
		i--;
	}
	//printf("%s\n",p);
	while(*p++ != ' ');
	while(*p != ',' && *p != ' ' && *p != ';' && *p != '\t' && *p != '\n' && *p != '.')
	{
		*buf = *p;	
		p++;
		buf++;
	}
	*buf = '\0';	
}
