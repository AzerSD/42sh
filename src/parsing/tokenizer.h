/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 01:58:31 by asioud            #+#    #+#             */
/*   Updated: 2023/02/16 01:38:42 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/**
 * This tokenizer file will use the helper functions created by the lexer.c file
 * to scan the input and turn them into tokens
*/


#ifndef TOKENIZER_H
# define TOKENIZER_H
# define EOF_TOKEN NULL

# include "lexer.h"


typedef struct s_curr_tok
{
	char    *tok_buff;
	int     tok_buff_size;
	int     tok_buff_index;
} t_curr_tok;

typedef struct s_token
{
	t_cli		*src;                /* holds our input */
	char		*text;               /* token text */
	int			text_len;            /* lthe parser is the part of our Command Line Interpreter that calls the lexical tokenizer to retrieve tokens, then constructs an Abstract Syntax Tree, or AST, out of these tokens. This AST is what we’ll pass to the executor to be, well, executed.ength of token text */
} t_token;

t_token *tokenize(t_cli *cli, t_curr_tok *curr);
void	init_curr_tok(t_curr_tok *curr);
void    free_token(t_token *tok);

#endif
