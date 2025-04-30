/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST_first_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:13:57 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/14 19:08:00 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

typedef struct s_node	t_node;

typedef enum s_ast_type
{
	CMD,
	PIPE,
	REDIR_IN,
	REDIR_OUT
}	t_ast_type;

typedef struct s_node
{
	t_ast_type	type;
	char	*value;
	t_node	*left;
	t_node	*right;
}	t_node;

t_node	*create_node(char *value, t_ast_type type)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	new_node->type = type;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

void	print_ast(t_node *node, int level)
{
	if (!node)
		return ;
	for (int i = 0; i < level; i++)
		printf("   ");
	switch (node->type)
	{
		case CMD:
			printf("|-- COMMAND : %s\n", node->value);
			break;
		case PIPE:
			printf("|-- PIPE\n");
			break;
		case REDIR_IN:
			printf("|-- REDIR_IN: %s\n", node->value);
			break;
		case REDIR_OUT:
			printf("|-- REDIR_OUT: %s\n", node->value);
			break;
	}
	print_ast(node->left, level + 1);
	print_ast(node->right, level + 1);
}

int	main(void)
{
	t_node	*first_cmd = create_node("cat", CMD);
	first_cmd->left = create_node("infile.txt", REDIR_IN);
	
	t_node	*second_cmd = create_node("grep", CMD);;
	second_cmd->left = create_node("\"hello\"", CMD);
	
	t_node	*pipe = create_node(NULL, PIPE);
	pipe->left = first_cmd;
	pipe->right = second_cmd;
	
	t_node	*redir_out = create_node("output.txt", REDIR_OUT);
	redir_out->left = pipe;

	printf("AST :\n");
	print_ast(redir_out, 0);
	return (0);
}
