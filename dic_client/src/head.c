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
int menu(void)
{
	char str[64];
	int i = 0;
	while((str[i] = getchar()) != '\n')
		i++;
	str[i] = '\0';
	return atoi(str); 
}

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
void help_viewer(void)
{
	FILE *fp = fopen("./doc/readme","r");
	if(fp == NULL){
		perror("readme");	
		exit(1);
	}
	char ch;
	while((ch = getc(fp)) != EOF)
		putchar(ch);
	fclose(fp);
}
void gate(void)
{
	char pass[] = "123";
	char buf[10];
	char ch;
	puts("Please input password:");
	int i = 3;
	int j = 0;
	while(i > 0)
	{
		j = 0;
		while((ch = getchar()) != '\n')	
		{
			buf[j++] = ch;
		}
		buf[j] = '\0';
		if(strcmp(pass,buf) == 0){
			puts("\t\tInentity Confirmed\tWelcome !");
			break;	
		}
		i--;
		if(i == 0){
			puts("Sorry,you don't have right to enter system.");	
			exit(1);
		}
		if(i == 1)
			printf("Password is incorrect,%d change left.\n",i);
		else
			printf("Password is incorrect,%d changes left.\n",i);
	}

}
