/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 01:58:38 by asioud            #+#    #+#             */
/*   Updated: 2023/02/23 09:08:17 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <errno.h>

#include "../core/shell.h"
#include "lexer.h"

void	unget_char(t_cli *cli)
{
	if(cli->cur_pos < 0)
		return;
	cli->cur_pos--;
}

char	next_char(t_cli *cli)
{
	char	c;

	if(!cli || !cli->buffer)
	{
		errno = ENODATA;
		return ERRCHAR;
	}
	c = 0;
	if(cli->cur_pos == INIT_SRC_POS)
		cli->cur_pos  = -1;
	else
		c = cli->buffer[cli->cur_pos];
	if(++cli->cur_pos >= cli->buff_size)
	{
		cli->cur_pos = cli->buff_size;
		return EOF;
	}
	return cli->buffer[cli->cur_pos];
}

char	peek_char(t_cli *cli)
{
	long int	pos;

	if(!cli || !cli->buffer)
	{
		errno = ENODATA;
		return ERRCHAR;
	}
	pos = cli->cur_pos;
	if(pos == INIT_SRC_POS)
		pos++;
	pos++;
	if(pos >= cli->buff_size)
		return EOF;
	return (cli->buffer[pos]);
}

void	skip_whitespaces(t_cli *cli)
{
	char	c;

	if(!cli || !cli->buffer)
		return;
	while(((c = peek_char(cli)) != EOF) && (c == ' ' || c == '\t'))
		next_char(cli);
}

