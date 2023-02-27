/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 01:54:40 by asioud            #+#    #+#             */
/*   Updated: 2023/02/27 11:00:11 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../core/shell.h"
#include "../symbol_table/symtab.h"

void prompt_display_ps1(void)
{
    struct s_symtab_entry *entry = get_symtab_entry("PS1");
    if(entry && entry->val)
    {
        fprintf(stderr, "%s", entry->val);
    }
    else
    {
        fprintf(stderr, "\033[1;32m$ ");
    }
}

void prompt_display_ps2(void)
{
    struct s_symtab_entry *entry = get_symtab_entry("PS2");

    if(entry && entry->val)
    {
        fprintf(stderr, "%s", entry->val);
    }
    else
    {
        fprintf(stderr, "\033[1;32m> ");
    }
}

