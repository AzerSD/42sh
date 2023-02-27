/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 01:58:27 by asioud            #+#    #+#             */
/*   Updated: 2023/02/23 09:09:55 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * This scanner file will use the helper functions created by the lexer.c file
 * to scan the input and turn them into tokens
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "../core/shell.h"
#include "tokenizer.h"
#include "lexer.h"

/*
 * add a single character to the token buffer
 * if the buffer is full, Extend it
*/
void add_to_buf(char c, t_curr_tok *curr)
{
    curr->tok_buff[curr->tok_buff_index++] = c;

    if(curr->tok_buff_index >= curr->tok_buff_size)
    {
        char *tmp = realloc(curr->tok_buff, curr->tok_buff_size*2);

        if(!tmp)
        {
            errno = ENOMEM;
            return;
        }
        curr->tok_buff = tmp;
        curr->tok_buff_size *= 2;
    }
}

/*
 * takes a string and converts it to s_token
*/
t_token *create_token(char *str)
{
    t_token *tok = malloc(sizeof(t_token));
    if(!tok)
        return NULL;
    memset(tok, 0, sizeof(t_token));
    tok->text_len = strlen(str);
    char *nstr = malloc(tok->text_len+1);
    if(!nstr)
    {
        free(tok);
        return NULL;
    }
    strcpy(nstr, str);
    tok->text = nstr;
    
    return tok;
}

/*
 * free the memory used by a token structure
*/
void free_token(t_token *tok)
{
    if(tok->text)
    {
        free(tok->text);
    }
    free(tok);
}

/*
 * Lexical Scanner 
 * allocate memory for token buffer and input pointer
 * keep retreaving next_char until EOF_INPUT
 * Loop to read input char by char, if it encounters a whitespace 
 * it checks the token buffer if it's empty or not, if the buff
 * is not empty we delimit the current token and break out of the loop 
 * otherwise we skip the whitespace char and move along to the beginning 
 * of the next token
 * After we’ve got our token, tokenize() calls create_token(), 
 * passing it the token text (which we stored in the buffer).
 * The token text is converted to a token structure, 
 * which tokenize() then returns to the caller.
*/
t_token *tokenize(t_cli *cli, t_curr_tok *curr)
{
    char    nc;
    
    init_curr_tok(curr);
    if (!cli || !cli->buffer || !cli->buff_size)
    {
        errno = ENODATA;
        return EOF_TOKEN;
    }
    
    if (!curr->tok_buff)
    {
        curr->tok_buff_size = 1024;
        curr->tok_buff = malloc(curr->tok_buff_size);
        if(!curr->tok_buff)
        {
            errno = ENOMEM;
            return EOF_TOKEN;
        }
    }

    curr->tok_buff_index = 0;
    curr->tok_buff[0] = '\0';
    nc = next_char(cli);

    if (nc == ERRCHAR || nc == EOF)
        return EOF_TOKEN;

    while (nc != EOF)
    {
        if (nc == ' ' || nc == '\t')
        {
            if (curr->tok_buff_index > 0)
                break;
        }
        else if (nc == '\n')
        {
            if (curr->tok_buff_index > 0)
                unget_char(cli);
            else
                add_to_buf(nc, curr);
            break;
        }
        else
            add_to_buf(nc, curr);
        nc = next_char(cli);
    }

    if(curr->tok_buff_index == 0)
        return EOF_TOKEN;
    
    if(curr->tok_buff_index >= curr->tok_buff_size)
        curr->tok_buff_index--;
    curr->tok_buff[curr->tok_buff_index] = '\0';

    t_token *tok = create_token(curr->tok_buff);
    if(!tok)
    {
        fprintf(stderr, "error: failed to alloc buffer: %s\n", strerror(errno));
        return EOF_TOKEN;
    }

    tok->src = cli;
    return tok;
}

void init_curr_tok(t_curr_tok *curr)
{
    curr->tok_buff = NULL;          // ptr to the buffer to store curr token
    curr->tok_buff_size = 0;        // nb of bytes we allocated to the buffer
    curr->tok_buff_index = -1;      // tells us where to put next character in buffer
}
