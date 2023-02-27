/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 07:05:51 by asioud            #+#    #+#             */
/*   Updated: 2023/02/27 11:02:25 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYMTAB_H
#define SYMTAB_H

#include "../parsing/node.h"


/**
 * the type of a symbol table entry's value
 * @param SYM_STR   Represent shell variables
 * @param SYM_FUNC  Represent functions
*/
enum e_symbol_type
{
    SYM_STR ,
    SYM_FUNC,
};

/**
 * The symbol table entry structure
 * @param name  The name of the shell variable represented by the entry
 * @param val_type  SYM_STR or SYM_FUNC
 * @param val   String value (for shell variables only)
 * @param flags Different properties assigned to variables and functions like export and readonly flags
 * @param next Pointer to the next symbol table entry
 * @param func_body For shell functions. The AST of the function body
*/
struct s_symtab_entry
{
    enum e_symbol_type      val_type;
    struct s_symtab_entry   *next;
    struct s_node           *func_body;
    unsigned int            flags;
    char                    *name;
    char                    *val;
};

/**
 * The symbol table structure
 * @param level For the global symbol table
 * @param first First entry in the table's linked list
 * @param last  Last entry in the table's linkes list
*/
struct s_symtab
{
    int                     level;
    struct s_symtab_entry   *first;
    struct s_symtab_entry   *last;
};

/* values for the flags field of struct s_symtab_entry */                       
#define FLAG_EXPORT (1 << 0) /* export entry to forked commands */

/* the symbol table stack structure */
#define MAX_SYMTAB	256  /* maximum allowed symbol tables in the stack */

/**
 * the symbol table stack structure
 * @param symtab_count The number of the global symbol table currently in the stack.
 * @param symtab_list   An array of pointers to the stack's symbol table
 * the stack holds up to MAX_SYMTAB.
 * @param global_symtab Pointers to the global symbol tables.
 * @param local_symtab Pointers to the local symbol tables.
*/
struct s_symtabtack_s
{
    int             symtab_count;
    struct s_symtab *symtab_list[MAX_SYMTAB];
    struct s_symtab *global_symtab;
    struct s_symtab *local_symtab;
};

int rem_from_symtab(struct s_symtab_entry *entry, struct s_symtab *symtab);

struct s_symtab_entry *do_lookup(char *str, struct s_symtab *symtable);
struct s_symtab_entry *add_to_symtab(char *symbol);
struct s_symtab_entry *get_symtab_entry(char *str);
struct s_symtabtack_s *get_s_symtabtack(void);
struct s_symtab       *s_symtabtack_push(void);
struct s_symtab       *get_global_symtab(void);
struct s_symtab       *s_symtabtack_pop(void);
struct s_symtab       *get_local_symtab(void);
struct s_symtab       *new_symtab(int level);

void symtab_entry_setval(struct s_symtab_entry *entry, char *val); 
void free_symtab(struct s_symtab *symtab);
void dump_local_symtab(void);
void init_symtab(void);

#endif