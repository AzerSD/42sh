/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 01:58:07 by asioud            #+#    #+#             */
/*   Updated: 2023/02/27 11:03:53 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#include "../core/shell.h"
#include "node.h"
#include "parser.h"


t_node *new_node(enum e_node_type type)
{
	t_node *node = malloc(sizeof(t_node));

	if(!node)
		return NULL;
	memset(node, 0, sizeof(t_node));
	node->type = type;
	return node;
}


void add_child_node(t_node *parent, t_node *child)
{
	if (!parent || !child)
		return;
	if (!parent->first_child)
		parent->first_child = child;
	else
	{
		t_node *sibling = parent->first_child;
	
		while (sibling->next_sibling)
			sibling = sibling->next_sibling;
		sibling->next_sibling = child;
		child->prev_sibling = sibling;
	}
	parent->children++;
}


void set_node_val_str(t_node *node, char *val)
{
	node->val_type = VAL_STR;

	if(!val)
	{
		node->val.str = NULL;
	}
	else
	{
		char *val2 = malloc(strlen(val)+1);
	
		if(!val2)
		{
			node->val.str = NULL;
		}
		else
		{
			strcpy(val2, val);
			node->val.str = val2;
		}
	}
}


void free_node_tree(t_node *node)
{
	if(!node)
	{
		return;
	}

	t_node *child = node->first_child;
	
	while(child)
	{
		t_node *next = child->next_sibling;
		free_node_tree(child);
		child = next;
	}
	
	if(node->val_type == VAL_STR)
	{
		if(node->val.str)
		{
			free(node->val.str);
		}
	}
	free(node);
}

