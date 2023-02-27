/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 01:55:30 by asioud            #+#    #+#             */
/*   Updated: 2023/02/27 11:03:07 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
#define SHELL_H

# define PS1 "$ "
# define PS2 "> "

// void prompt_display(char *ps);
void prompt_display_ps1(void);
void prompt_display_ps2(void);

char *get_cmd(void);

#include "../parsing/lexer.h"

int  parse_and_execute(t_cli *cli);
void initsh(void);

/* shell builtin utilities */
int dump(int argc, char **argv);

/* struct for builtin utilities */
struct s_builtin
{
    char *name;    /* utility name */
    int (*func)(int argc, char **argv); /* function to call to execute the utility */
};

/* the list of builtin utilities */
extern struct s_builtin builtins[];

/* and their count */
extern int builtins_count;

#endif

// Practic more vim 
// Understand your code 
// do some german 
// Read your book 
// Do cpp
// Be mindfullness
// Prepare for the exam
// You've got this big things are coming your way you can do it trust me
// alhamdoulelellahh 
// remember your ambitions and dreams and goalsss
// you wanna achieve it
// do what you have to do
// and fucking stick to it

