/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 01:45:52 by asioud            #+#    #+#             */
/*   Updated: 2023/02/27 02:33:16 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

#include "./shell.h"
#include "../parsing/lexer.h"
#include "../parsing/parser.h"
#include "../execution/executor.h"
#include "../symbol_table/symtab.h"
#include "../../libs/libft/includes/libft.h"

int main(int argc, char **argv)
{
	t_cli		cli;
	char		*cmd;

	(void) argc;
	(void) argv;
	initsh();
	while (true)
	{
		prompt_display_ps1();
		cmd = get_cmd();
		if(!cmd)
			exit(EXIT_SUCCESS);
		if(cmd[0] == '\0' || strncmp(cmd, "\n", 1) == 0)
		{
			free(cmd);
			continue;
		}
		if(strncmp(cmd, "exit\n", 5) == 0)
		{
			free(cmd);
			break;
		}
		cli.buffer   = cmd;
		cli.buff_size  = strlen(cmd);
		cli.cur_pos   = INIT_SRC_POS;
		parse_and_execute(&cli);
		free(cmd);
	}
	exit(EXIT_SUCCESS);
}

char *get_cmd(void)
{
	char	*buf;
	char	*ptr = NULL;
	char	ptrlen = 0;
	char	*ptr2;
	int		buff_len;

	while ((buf = get_next_line(0)))
	{
		buff_len = strlen(buf);
		if (!ptr)
			ptr = malloc(buff_len + 1);
		else
		{
			ptr2 = realloc(ptr, ptrlen + buff_len + 1);
			if (ptr2)
				ptr = ptr2;
			else
			{
				free(ptr);
				ptr = NULL;
			}
		}
		if (!ptr)
		{
			ft_printf_fd(2, "error: failed to alloc buffer: %s\n", strerror(errno));
			return NULL;
		}
		strlcpy(ptr+ptrlen, buf, buff_len + 1);
		if (buf[buff_len - 1] == '\n')
		{
			if (buff_len == 1 || buf[buff_len - 2] != '\\')
				return ptr;
			ptr[ptrlen + buff_len - 2] = '\0';
			buff_len -= 2;
			prompt_display_ps2();
		}
		ptrlen += buff_len;
	}
	return ptr;
}

int parse_and_execute(t_cli *cli)
{
	t_node		*cmd;
	t_token		*tok;
	t_curr_tok	*curr = malloc(sizeof(t_curr_tok));

	skip_whitespaces(cli);

	tok = tokenize(cli, curr);

	if(tok == EOF_TOKEN)
		return 0;
	while(tok && tok != EOF_TOKEN)
	{
		cmd = parse_simple_command(tok);
		if(!cmd)
			break;
		execc(cmd);
		free_node_tree(cmd);
		tok = tokenize(cli, curr);
	}
	return 1;
}
