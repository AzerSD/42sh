/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 05:41:31 by asioud            #+#    #+#             */
/*   Updated: 2023/02/27 11:03:07 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../core/shell.h"

struct s_builtin builtins[] =
{   
    { "dump"    , dump },
};

int builtins_count = sizeof(builtins)/sizeof(struct s_builtin);