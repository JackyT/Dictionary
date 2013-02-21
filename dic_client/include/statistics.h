/*
 * =====================================================================================
 *
 *       Filename:  stactics.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年08月09日 15时57分51秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef  _STATISTICS_H
#define _STATISTICS_H
typedef struct node *Link;
struct node{
	char *item;
	int counter;
	Link l,r;
};

void addto_root_file(const char *file_name,const char *word);

Link make_node(char *key);
Link make_node_sec(char *key,int time);
void traverse(Link p);
void print_bst(Link p,int level,char lr);
void Link_destroy(Link p);
Link max(Link p);
#define MAX_COUNTER(a,b) (a->counter > b->counter)? a : b
Link getmax_counter(Link p1,Link p2);
Link max_counter(Link p);
Link insert(Link p,char *key);
Link insert_sec(Link p,char *key,int time);
Link delete(Link t,char *key);
Link scan_root_file(Link stac,const char *file_name);
Link root_sort(Link root);
#endif     /* -----  not _STATISTCS_H  ----- */
