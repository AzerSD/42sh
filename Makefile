# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asioud <asioud@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/25 10:59:44 by asioud            #+#    #+#              #
#    Updated: 2023/02/25 11:20:54 by asioud           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	sh
CC			=	cc
RM			=	rm -rf
LIBFT		= 	libs/libft/libft.a
CFLAGS		=	-Wall -Wextra -Werror

SRC	=	core/shell \
		builtins/builtins \
		builtins/dump \
		prompt/prompt \
		symbol_table/init_symtab \
		symbol_table/symtab \
		execution/executor \
		parsing/lexer \
		parsing/node \
		parsing/parser \
		parsing/tokenizer \

SRC_DIR		=	src/
OBJ_DIR		=	obj/

SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC)))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC)))

all:	$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LIBFT) $(OBJS) -o $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)

fclean:	clean
	@$(RM) $(NAME)

re:	fclean all

.PHONY:	all bonus clean fclean re

