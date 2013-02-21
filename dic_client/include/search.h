/*
 * =====================================================================================
 *
 *       Filename:  search.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年08月09日 10时30分44秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef  _SEARCH_H
#define _SEARCH_H

WORD *word_search(WORD *head,char *str);
WORD *part_search(WORD *head,char ch);

WORD *part_word_look(WORD *head,char *str,int size);
#endif     /* -----  not _SEARCH_H  ----- */
