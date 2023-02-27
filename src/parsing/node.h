/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 01:58:12 by asioud            #+#    #+#             */
/*   Updated: 2023/02/27 11:04:32 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef NODE_H
#define NODE_H

/**
 * Define the type of our AST Node
 * @param NODE_COMMAND represents the root node of a simple command
 * @param NODE_VAR	represents the simple command's child nodes
*/
enum e_node_type
{
	NODE_COMMAND,           /* simple command */
	NODE_VAR,               /* variable name (or simply, a word) */
};

/**
 * Represents the types of values we can store in a given node structure
 * for simple commands we use only VAL_STR
*/
enum e_val_type
{
	VAL_SINT = 1,       /* signed int */
	VAL_UINT,           /* unsigned int */
	VAL_SLLONG,         /* signed long long */
	VAL_ULLONG,         /* unsigned long long */
	VAL_FLOAT,          /* floating point */
	VAL_LDOUBLE,        /* long double */
	VAL_CHR,            /* char */
	VAL_STR,            /* str (char pointer) */
};

/**
 * Represents the value we can store in a given node structure,
 * Each node can have only one typoe of value.
*/
union u_symval
{
	unsigned long long ullong;
	unsigned long      uint;
	long long          sllong;
	long double        ldouble;
	double             sfloat;
	long               sint;
	char               chr;
	char              *str;
};

/**
 * Represents an AST node. it contains fields that tell us about
 * the node's type, the type of the node's value and the value itself
 * and pointers to children nodes and sibling nodes.
*/
typedef struct s_node
{
	enum e_node_type	type;		/* type of this node */
	enum e_val_type		val_type;	/* type of this node's val field */
	union u_symval		val;		/* value of this node */
	int					children;	/* number of child nodes */
	struct s_node		*first_child;	/* first child node */
	struct s_node		*next_sibling;
	struct s_node		*prev_sibling;	/*
										 * if this is a child node, keep
									 	 * pointers to prev/next siblings
										*/
} t_node ;

t_node	*new_node(enum e_node_type type);
void    add_child_node(t_node *parent, t_node *child);
void    free_node_tree(t_node *node);
void    set_node_val_str(t_node *node, char *val);

#endif


// If we want to retrieve a node’s value, we need to check the val_type field and, according to what we find there, access the appropriate member of the val field. For simple commands, all nodes will have the following attributes:

//     type => NODE_COMMAND (root node) or NODE_VAR (command name and arguments list)
//     val_type => VAL_STR
//     val.str => pointer to the string value