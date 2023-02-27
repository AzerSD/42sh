/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 07:28:23 by asioud            #+#    #+#             */
/*   Updated: 2023/02/27 11:01:53 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../core/shell.h"
#include "../parsing/node.h"
#include "../parsing/parser.h"
#include "symtab.h"

struct s_symtabtack_s s_symtabtack; // pointer to our symbol table stack (we only need one stack per shell).
int    symtab_level; // our current level in the stack (0 if we're working with the global symbol table, non-zero otherwise).

/**
 * Initializes our symbol table stack, then allocates memory for,
 * and initializes, our global symbol table.
*/
void init_symtab(void)
{
	struct s_symtab *global_symtab = malloc(sizeof(struct s_symtab));
	
	s_symtabtack.symtab_count = 1;
	symtab_level = 0;
	if(!global_symtab)
	{
		fprintf(stderr, "fatal error: no memory for global symbol table\n");
		exit(EXIT_FAILURE);
	}
	memset(global_symtab, 0, sizeof(struct s_symtab));
	s_symtabtack.global_symtab  = global_symtab;
	s_symtabtack.local_symtab   = global_symtab;
	s_symtabtack.symtab_list[0] = global_symtab;
	global_symtab->level        = 0;
}

/**
 * Called when we're done working with a symbol table,
 * and we want to free the memory used by the symbol table and its entries.
*/
void free_symtab(struct s_symtab *symtab)
{
	if(symtab == NULL)
		return;
	struct s_symtab_entry *entry = symtab->first;
	while(entry)
	{
		if(entry->name)
			free(entry->name);
		if(entry->val)
			free(entry->val);
		if(entry->func_body)
			free_node_tree(entry->func_body);
		struct s_symtab_entry *next = entry->next;
		free(entry);
		entry = next;
	}
	free(symtab);
}

/**
 * Debugging function
 * This function prints the contents of the local symbol table.
 * When our shell starts, the local and global symbol tables will
 * refer to the same table. It is only when the shell is about to
 * run a shell function or script file that we have a local table
 * that is different from the global table.
 * (later on in this lesson, we’ll write a builtin utility that
 * will call dump_local_symtab() to help us visualize the contents
 * of our shell's global symbol table).
*/
void dump_local_symtab(void)
{
	struct s_symtab *symtab = s_symtabtack.local_symtab;
	int i = 0;
	int indent = symtab->level * 4;
	fprintf(stderr, "%*sSymbol table [Level %d]:\r\n", indent, " ", symtab->level);
	fprintf(stderr, "%*s===========================\r\n", indent, " ");
	fprintf(stderr, "%*s  No               Symbol                    Val\r\n", indent, " ");
	fprintf(stderr, "%*s------ -------------------------------- ------------\r\n", indent, " ");
	struct s_symtab_entry *entry = symtab->first;
	while(entry)
	{
		fprintf(stderr, "%*s[%04d] %-32s '%s'\r\n", indent, " ",
				i++, entry->name, entry->val);
		entry = entry->next;
	}
	fprintf(stderr, "%*s------ -------------------------------- ------------\r\n", indent, " ");
}

/**
 * This function adds a new entry to the local symbol table. Remember,
 * To ensure that each entry has a unique key, we first check to see
 * if an entry exists with the given name, by calling do_lookup()
 * If an entry with the given name exists, we simply return the existing entry,
 * without adding a new one.Otherwise, we add the entry, set its name,
 * and adjust the symbol table's pointers. Lastly, we return the newly added entry.
*/
struct s_symtab_entry *add_to_symtab(char *symbol)
{
	if(!symbol || symbol[0] == '\0')
		return NULL;
	struct s_symtab *st = s_symtabtack.local_symtab;
	struct s_symtab_entry *entry = NULL;
	
	if((entry = do_lookup(symbol, st)))
		return entry;
		
	entry = malloc(sizeof(struct s_symtab_entry));
	if(!entry)
	{
		fprintf(stderr, "fatal error: no memory for new symbol table entry\n");
		exit(EXIT_FAILURE);
	}
	memset(entry, 0, sizeof(struct s_symtab_entry));
	entry->name = malloc(strlen(symbol)+1);
	if(!entry->name)
	{
		fprintf(stderr, "fatal error: no memory for new symbol table entry\n");
		exit(EXIT_FAILURE);
	}
	strcpy(entry->name, symbol);
	if(!st->first)
	{
		st->first      = entry;
		st->last       = entry;
	}
	else
	{
		st->last->next = entry;
		st->last       = entry;
	}
	return entry;
}

/**
 * Opposite of symbtab_entry_s 
 * it removes the symbol table entry whose key matches the given name
 * and frees the memory used by the entry and adjusts the linked list pointers to 
 * remove the entry from the symbol table
*/
int rem_from_symtab(struct s_symtab_entry *entry, struct s_symtab *symtab)
{
	int res = 0;
	if(entry->val)
		free(entry->val);
	if(entry->func_body)
		free_node_tree(entry->func_body);
	free(entry->name);
	if(symtab->first == entry)
	{
		symtab->first = symtab->first->next;
		if(symtab->last == entry)
			symtab->last = NULL;
		res = 1;
	}
	else
	{
		struct s_symtab_entry *e = symtab->first;
		struct s_symtab_entry *p = NULL;
		while(e && e != entry)
		{
			p = e;
			e = e->next;
		}
		if(e == entry)
		{
			p->next = entry->next;
			res = 1;
		}
	}
	free(entry);
	return res;
}

/**
 * This function searches the given symbol table, starting with the first entry.
 * If the entry’s key matches the variable name we’re looking for,
 * the function returns the entry. Otherwise, the function follows the linked
 * list pointers to look at each entry, in turn, until we find an entry whose
 * key matches our desired name. If no match is found, we return NULL.
*/
struct s_symtab_entry *do_lookup(char *str, struct s_symtab *symtable)
{
	if(!str || !symtable)
		return NULL;
	struct s_symtab_entry *entry = symtable->first;
	while(entry)
	{
		if(strcmp(entry->name, str) == 0)
			return entry;
		entry = entry->next;
	}
	return NULL;
}

/**
 * searches for a symbol table entry whose key matches the given name.
 * The difference between this function and do_lookup() is this function searchs
 * the whole stack starting with the local symbol table.
 * This function is usefull for shell functions and script files.
*/
struct s_symtab_entry *get_symtab_entry(char *str)
{
	int i = s_symtabtack.symtab_count-1;
	do
	{
		struct s_symtab *symtab = s_symtabtack.symtab_list[i];
		struct s_symtab_entry *entry = do_lookup(str, symtab);
		if(entry)
		{
			return entry;
		}
	} while(--i >= 0);
	return NULL;
}

/**
 * This function frees the memory used to store the old entry’s value
 * (if one exists). It then creates a copy of the new value and stores
 * it in the symbol table entry.
*/
void symtab_entry_setval(struct s_symtab_entry *entry, char *val)
{
	if(entry->val)
	{
		free(entry->val);
	}    if(!val)
	{
		entry->val = NULL;
	}
	else
	{
		char *val2 = malloc(strlen(val)+1);        if(val2)
		{
			strcpy(val2, val);
		}
		else
		{
			fprintf(stderr, "error: no memory for symbol table entry's value\n");
		}        entry->val = val2;
	}
}

///////////////////// Symbol Table Stack Functions ///////////////////////

/**
 *  adds the given symbol table to the stack, and assigns the newly added table as the local symbol table.
*/
void s_symtabtack_add(struct s_symtab *symtab)
{
	s_symtabtack.symtab_list[s_symtabtack.symtab_count++] = symtab;
	s_symtabtack.local_symtab = symtab;
}

/**
 * creates a new, empty symbol table and pushes it on top of the stack.
*/
struct s_symtab *s_symtabtack_push(void)
{
	struct s_symtab *st = new_symtab(++symtab_level);
	s_symtabtack_add(st);
	return st;
}

/**
 * removes (or pops) the symbol table on top of the stack, adjusting the stack pointers as needed.
*/
struct s_symtab *s_symtabtack_pop(void)
{
	if(s_symtabtack.symtab_count == 0)
		return NULL;
	struct s_symtab *st = s_symtabtack.symtab_list[s_symtabtack.symtab_count-1];
	s_symtabtack.symtab_list[--s_symtabtack.symtab_count] = NULL;
	symtab_level--;
	if(s_symtabtack.symtab_count == 0)
	{
		s_symtabtack.local_symtab  = NULL;
		s_symtabtack.global_symtab = NULL;
	}
	else
		s_symtabtack.local_symtab = s_symtabtack.symtab_list[s_symtabtack.symtab_count-1];
	return st;
}

/**
 * return pointers to the local symbol tables.
*/
struct s_symtab *get_local_symtab(void)
{
	return s_symtabtack.local_symtab;
}

/**
 * return pointers to the global symbol tables.
*/
struct s_symtab *get_global_symtab(void)
{
	return s_symtabtack.global_symtab;
}

/**
 * returns a pointer to the symbol table stack.
*/
struct s_symtabtack_s *get_s_symtabtack(void)
{
	return &s_symtabtack;
}
