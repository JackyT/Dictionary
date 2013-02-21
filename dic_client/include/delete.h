/*
 * =====================================================================================
 *
 *       Filename:  delete.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年08月09日 13时02分21秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef  _DELETE_H
#define _DELETE_H

typedef struct delt{
	char *del;
	struct delt *next;	
}DELETE;
void delete_word(const char *word);
DELETE *scan_del_doc(DELETE *deled);
DELETE *make_del_node(DELETE *deled,char *del);
void free_del_link(DELETE *deled);
DELETE *del_word_search(DELETE *head,const char *str);
#endif     /* -----  not _DELETE_H  ----- */
