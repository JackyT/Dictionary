/*
 * =====================================================================================
 *
 *       Filename:  head.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年08月10日 11时14分31秒
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
#include "head.h"

int part_word_proc(char *str)
{
	int i = 0;
	while(*str != '*' && *str != '\0')
	{
		str++;
		i++;
	}
	*str = '\0';
	return i;
}

void input(char *str)
{
	char ch;
	while((ch = getchar()) == ' ');
	while(1)
	{
		if(ch == '\n')	
			break;
		*str++ = ch;
		ch = getchar();
	}
	*str = '\0';
	//printf("%s\n",str);
}

