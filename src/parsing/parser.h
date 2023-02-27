/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 01:58:21 by asioud            #+#    #+#             */
/*   Updated: 2023/02/18 06:35:50 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef PARSER_H
#define PARSER_H

#include "tokenizer.h"    /* t_token */
#include "lexer.h"     /* t_cli */
#include "node.h"

t_node *parse_simple_command(t_token *tok);

#endif
