/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_symtab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 05:28:17 by asioud            #+#    #+#             */
/*   Updated: 2023/02/27 11:01:31 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "symtab.h"
#include "../core/shell.h"
#include "../parsing/node.h"
#include "../parsing/parser.h"

extern char **environ;

/**
 * This function initializes the symbol table stack (including the global
 * symbol table) and scans the environment list, adding each environment
 * variable (and its value) to the table. Lastly, the function adds two
 * variables that we’ll use to store our prompt strings, PS1 and PS2
*/
void initsh(void)
{
    init_symtab();
    struct s_symtab_entry *entry;
    char **p2 = environ;
    while(*p2)
    {
        char *eq = strchr(*p2, '=');
        if(eq)
        {
            int len = eq-(*p2);
            char name[len+1];
            strncpy(name, *p2, len);
            name[len] = '\0';
            entry = add_to_symtab(name);
            if(entry)
            {
                symtab_entry_setval(entry, eq+1);
                entry->flags |= FLAG_EXPORT;
            }
        }
        else
            entry = add_to_symtab(*p2);
        p2++;
    }
    entry = add_to_symtab("$ ");
    symtab_entry_setval(entry, PS1);
    entry = add_to_symtab("> ");
    symtab_entry_setval(entry, PS2);
}

/**
 * create a new symbol table
*/
struct s_symtab *new_symtab(int level)
{
    struct s_symtab *symtab = malloc(sizeof(struct s_symtab));
    if(!symtab)
    {
        fprintf(stderr, "fatal error: no memory for new symbol table\n");
        exit(EXIT_FAILURE);
    }
    memset(symtab, 0, sizeof(struct s_symtab));
    symtab->level = level;
    return symtab;
}