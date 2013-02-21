/*
 * =====================================================================================
 *
 *       Filename:  add.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年08月09日 10时53分37秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "link.h"
#include "add.h"
void add_proc(char *word, char *trans)
{
	int i = 0;
	#if 0
	while(word[i] != '\0')
		i++;
	word[i++] = '\0';
	i--;
	while(i > 0)
	{
		word[i] = word[i-1];
		i--;
	}
	word[0] = '#';
	#endif
	//printf("%s\n",word);
	i = 0;
	while(trans[i] != '\0')
		i++;
	i = i + 7;
	trans[i] = '\0';
	i--;
	while(i > 5)
	{
		trans[i] = trans[i-6];
		i--;
	}
	trans[i--] = ':';
	trans[i--] = 's';
	trans[i--] = 'n';
	trans[i--] = 'a';
	trans[i--] = 'r';
	trans[i] = 'T';
	//printf("%s\n",trans);
}
void add_word(const char *word,const char *trans)
{
	FILE *fp = fopen("doc/ADD_WORD.txt","a+");
	if(fp == NULL){
		perror("ADD_WORD");	
		exit(1);
	}
#if 0 
	if(getc(fp) == EOF)
		fseek(fp,0,SEEK_SET);
	else{
		fseek(fp,0,SEEK_SET);
		head_add = scan_file("ADD_WORD.txt","a+",head_add);
	}
#endif
	char word_buf[128];	
	char trans_buf[1024];
	int i;
	word_buf[0] = '#';
	i = 1;
	while(*word != '\0')
	{
		word_buf[i++] = *word++;
	}
	word_buf[i++] = '\n';
	word_buf[i] = '\0';

	while(*trans != '\0')
	{
		trans_buf[i++] = *trans++;	
	}
	trans_buf[i++] = '\n';
	trans_buf[i] = '\0';

	fprintf(fp,"%s",word_buf);
	fprintf(fp,"%s",trans_buf);

	
	fclose(fp);
	return;

}
