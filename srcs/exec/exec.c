/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:08:09 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/10 11:31:54 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include <signal.h>

static t_cmd *ft_create_node(t_cmd *cmd_list, t_token *lexicon)
{
	t_cmd *new_node;
	int	i;
	static int tmp = 1;

	i = 0;
	new_node = malloc(sizeof(t_cmd));
	cmd_list = NULL;
	ft_memset(new_node, 0, sizeof(t_cmd));
	if (!lexicon || !cmd_list)
		return (NULL);
	if (!new_node)
		return (NULL);
	while (lexicon->index < tmp)
		lexicon =lexicon->next;
	while (lexicon->next)
	{
		if (lexicon->type == CMD)
		{
			new_node->args = malloc(sizeof(char *) * 10);
			new_node->args[i] = lexicon->value;
			lexicon = lexicon->next;
			while (lexicon->type == WORD)
			{
				i++;
				new_node->args[i] = lexicon->value;
				lexicon = lexicon->next;
			}
			i++;
			new_node->args[i] = NULL;
		}
		if (lexicon->type == INFILE)
		{
			new_node->infile = lexicon->value;
			lexicon = lexicon->next;
		}
		if (lexicon->type == OUTFILE)
		{
			new_node->outfile = lexicon->value;
			lexicon = lexicon->next;
		}
		if (lexicon->type == PIPE)
		{
			new_node->pipe = true;
			lexicon = lexicon->next;
			tmp = lexicon->index;
			break ;
		}
	}
	if (!cmd_list->next)
		*cmd_list = *new_node;
	else
	{
		while (cmd_list->next != NULL)
			cmd_list = cmd_list->next;
		cmd_list->next = new_node;
	}
	return (cmd_list);
}

static t_cmd *create_exec_list(t_cmd *cmd_list, t_token *lexicon)
{
	cmd_list = malloc(sizeof(t_cmd));
	if (!cmd_list)
		return (NULL);
	ft_memset(cmd_list, 0, sizeof(t_cmd));
	if (!cmd_list)
		cmd_list = ft_create_node(cmd_list, lexicon);
	else
	{
		while (cmd_list->next)
			cmd_list = cmd_list->next;
		cmd_list->next = ft_create_node(cmd_list, lexicon);
	}
	return (cmd_list);
}

int exec(t_token *lexicon)
{
	t_cmd	*cmd_list;
	// int		i;
	
	cmd_list = create_exec_list(NULL, lexicon);
	while (cmd_list)
	{
		// i = 0;
		// while (temp->args[i])
		// {
		// 	printf("n'%d args %s \n", i, temp->args[i]);
		// 	i++;
		// }
		printf("infile: %s \n outfile: %s \n append: %d \n pipe: %d \n heredoc: %s \n", cmd_list->infile, cmd_list->outfile, cmd_list->append, cmd_list->pipe, cmd_list->heredoc);
		cmd_list = cmd_list->next;
	}
	return (1);
}

	// while (lexicon)
	// {
	// 	printf("LEXICON//	value: %s \n token: %d \n index: %d \n\n", lexicon->value, lexicon->type, lexicon->index);
	// 	lexicon = lexicon->next;
	// }
