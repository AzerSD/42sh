/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 01:58:43 by asioud            #+#    #+#             */
/*   Updated: 2023/02/16 01:31:47 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Lexical analysis 
 * The data and function here will read input 
 * to make it easier to convert them into tokens
*/

#ifndef LEXER_H
# define LEXER_H

# define EOF (-1)
# define ERRCHAR (0)

# define INIT_SRC_POS (-2)

# include <stdlib.h>

/**
 * This struct represents our command line
*/
typedef struct s_cli
{
	char		*buffer;
	long int	buff_size;
	long int	cur_pos;
}	t_cli;

char			next_char(t_cli *cli);

char			peek_char(t_cli *cli);

void			unget_char(t_cli *cli);

void			skip_whitespaces(t_cli *cli);

#endif
