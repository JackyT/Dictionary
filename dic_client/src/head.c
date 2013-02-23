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
#include <curses.h>
#include "head.h"

void print_list(void)
{
	printf("\n\n\n\n");
	printf("\t\t|-------------------menu-----------------|\n");
	printf("\t\t|-------| 1.   search one word   |-------|\n");
	printf("\t\t|-------| 2.     misty search    |-------|\n");
	printf("\t\t|-------| 3.    add one word     |-------|\n");
	printf("\t\t|-------| 4.   delete one word   |-------|\n");
	printf("\t\t|-------| 5.      statistics     |-------|\n");
	printf("\t\t|-------| 6. sentence translator |-------|\n");
	printf("\t\t|-------| 7. search from remote  |-------|\n");
	printf("\t\t|-------| 8.   change password   |-------|\n");
	printf("\t\t|-------| 9.        help         |-------|\n");
	printf("\t\t|-------| 10.       exit         |-------|\n");
	printf("\t\t|----------------------------------------|\n");
	printf("\n\n");
	printf("please enter 1~10\n");
}
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
	FILE *fp = fopen("./doc/password","r");
	char pass[17];
	char buf[17];
	size_t wordsize= fread(pass,sizeof(char),sizeof(pass),fp);	
	pass[wordsize] = '\0';
	//puts(pass);	
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
			if(j > 16){
				printf("\nThe password is limited to 16.Please input your password again.\n");		
				i = 0;
				continue;
			}
		}
		buf[j] = '\0';
		if(strncmp(pass,buf,wordsize) == 0){
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
	fclose(fp);

}
int password_input(char *password,int sizelimit)
{
	int i = 0;
	char ch;
	int overflag = 0;
	while(1)
	{
		if((ch = getchar()) == '\n')	
			break;
		if(i >= sizelimit){
			password[sizelimit] = '\0';
			overflag = 1;
			continue;
		}
		password[i++] = ch;
		//addch('*');

	}
	if(overflag == 1)
		return -1;
	password[i] = '\0';
	return 0;
}
