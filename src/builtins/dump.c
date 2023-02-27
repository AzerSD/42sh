/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 05:42:20 by asioud            #+#    #+#             */
/*   Updated: 2023/02/23 11:34:28 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../core/shell.h"
#include "../symbol_table/symtab.h"

int dump(int argc, char **argv)
{
    (void) argc;
    (void) argv;
    dump_local_symtab();
    return 0;
}