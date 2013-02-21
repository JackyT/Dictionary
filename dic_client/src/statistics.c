#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "statistics.h"
Link make_node(char *key)
{
	Link p;
	p = malloc(sizeof(struct node));
	assert(p);
	p->item = malloc(sizeof(char)*(strlen(key)+1));
	assert(p->item);

	strcpy(p->item,key);
	p->counter = 1;
	p->l = NULL;
	p->r = NULL;
	return p;
}
Link make_node_sec(char *key,int time)
{
	Link p;
	p = malloc(sizeof(struct node));
	assert(p);
	p->item = malloc(sizeof(char)*(strlen(key)+1));
	assert(p->item);

	strcpy(p->item,key);
	p->counter = time;
	p->l = NULL;
	p->r = NULL;
	return p;
}
void traverse(Link p)
{
	if(p == NULL)
		return;
	traverse(p->l);
	printf("%s\t%d\n",p->item,p->counter);
	traverse(p->r);
}


void Link_destroy(Link p)
{
	if(p == NULL)
		return;
	Link_destroy(p->l);
	Link_destroy(p->r);
	free(p->item);
	free(p);
	return;
}
Link getmax_counter(Link p1,Link p2)
{
	if(p1 == NULL)
		return p2;
	if(p2 == NULL)
		return p1;
	return MAX_COUNTER(p1,p2);
}
Link max_counter(Link p)
{
	if(p == NULL)
		return NULL;
	Link pl,pr;
	pl = max_counter(p->l);
	pr = max_counter(p->r);

	return getmax_counter(p,getmax_counter(pl,pr));
}
Link insert(Link p,char *key)
{
	if(p == NULL)
		return make_node(key);
	if(strcmp(p->item,key) == 0){
		p->counter++;
		return p;
	}
	if(strcmp(key , p->item) < 0)
		p->l = insert(p->l,key);
	else if(strcmp(key , p->item) > 0)
		p->r = insert(p->r,key);
	return p;
}
Link insert_sec(Link p,char *key,int time)
{
	if(p == NULL)
		return make_node_sec(key,time);
	if(strcmp(p->item,key) == 0){
		p->counter++;
		return p;
	}
	if(strcmp(key , p->item) < 0)
		p->l = insert_sec(p->l,key,time);
	else if(strcmp(key , p->item) > 0)
		p->r = insert_sec(p->r,key,time);
	return p;
}

Link delete(Link t,char *key)
{
	Link p;
	if(t == NULL)
		return NULL;
	if(strcmp(key , t->item) < 0)
		t->l = delete(t->l,key);
	else if(strcmp(key , t->item) > 0)
		t->r = delete(t->r,key);
	else{ // key == p->item
		if(t->l == NULL && t->r == NULL){
			free(t->item);
			free(t);
			t = NULL;
		}else if(t->l != NULL){
			for(p = t->l;p->r != NULL;p = p->r);
			free(t->item);
			t->item = malloc(strlen(p->item) + 1);
			strcpy(t->item , p->item);
			t->counter = p->counter;
			t->l = delete(t->l,t->item);
		}else{// t->r != NULL
			for(p = t->r;p->l != NULL;p = p->l);	
			free(t->item);
			t->item = malloc(strlen(p->item) + 1);
			strcpy(t->item , p->item);
			t->counter = p->counter;
			t->r = delete(t->r,t->item);
		}

	}
	return t;
}

Link scan_root_file(Link stac,const char *file_name)
{
	char ch;
	FILE *fp = fopen(file_name,"r");
	assert(fp);
	char buf[128];
	int i = 0;
	while(1)
	{
		ch = getc(fp);
		if(ch == EOF)
			break;
		i = 0;
		while(ch != '\n')
		{
			buf[i++] = ch;
			ch = getc(fp);
		}
		buf[i] = '\0';
		stac = insert(stac,buf);	
	}
	fclose(fp);
	return stac;
}
void addto_root_file(const char *file_name,const char *word)
{
	FILE *fp = fopen(file_name,"a+");
	if(fp == NULL){
		perror(file_name);	
		exit(1);
	}
	fprintf(fp,"%s",word);
	putc('\n',fp);
	fclose(fp);
}
#if 1 
Link root_sort(Link root)
{	
	Link p = NULL;

	Link root2 = NULL;
	int index = 1;
	while(root != NULL)
	{
		p = max_counter(root);	
		root2 = insert_sec(root2,p->item,p->counter);
		printf("%-5dword: %-20s \n\t\t\ttimes: %d\n\n",index,p->item,p->counter);
		printf("...............................................\n");
		root = delete(root,p->item);
		index++;
	}

	//destroy(root);
	return root2;
}
#endif
