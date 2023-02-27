/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 01:57:59 by asioud            #+#    #+#             */
/*   Updated: 2023/02/27 02:33:16 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "../parsing/node.h"

char *search_path(char *file);
int exec_cmd(int argc, char **argv);
int execc(t_node *node);

#endif
