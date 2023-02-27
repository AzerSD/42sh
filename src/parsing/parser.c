/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 01:58:16 by asioud            #+#    #+#             */
/*   Updated: 2023/02/23 09:09:22 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <unistd.h>
#include <stdio.h>

#include "../core/shell.h"
#include "parser.h"
#include "tokenizer.h"
#include "node.h"
#include "lexer.h"

// the parser is the part of our Command Line Interpreter that calls
// the lexical tokenizer to retrieve tokens, then constructs an 
// Abstract Syntax Tree, or AST, out of these tokens.
// This AST is what we’ll pass to the executor to be, well, executed.

t_node *parse_simple_command(t_token *tok)
{
    t_curr_tok *curr = malloc(sizeof(t_curr_tok));
    if(!tok)
        return NULL;
    
    t_node *cmd = new_node(NODE_COMMAND);
    if(!cmd)
    {
        free_token(tok);
        return NULL;
    }
    t_cli *cli = tok->src;
    do
    {
        if(tok->text[0] == '\n')
        {
            free_token(tok);
            break;
        }
        t_node *word = new_node(NODE_VAR);
        if(!word)
        {
            free_node_tree(cmd);
            free_token(tok);
            return NULL;
        }
        set_node_val_str(word, tok->text);
        add_child_node(cmd, word);
        free_token(tok);
    } while((tok = tokenize(cli, curr)) != EOF_TOKEN);
    return cmd;
}
