/*
 * =====================================================================================
 *
 *       Filename:  link.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年08月08日 17时50分26秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef  _LINK_H
#define _LINK_H

typedef struct words WORD;
struct words{
	char *word;
	char *trans;
	struct words *next;
};

void destroy(WORD *head);
void traverse_link(WORD *head);
WORD *creat_one_node_to_head(WORD *head,char *word,char *trans);
WORD *scan_file(char *file_name,char *parameter,WORD *head);
void trans_process(char *str);
#endif     /* -----  not _LINK_H  ----- */
