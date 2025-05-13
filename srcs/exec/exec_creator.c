/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_creator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:08:09 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/13 16:40:26 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include <signal.h>

void	free_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*temp;

	temp = cmd_list;
	while (temp)
	{
		if (temp->args)
			free_tab(temp->args);
		if (temp->infile)
			free(temp->infile);
		if (temp->outfile)
			free(temp->outfile);
		if (temp->heredoc_delim)
			free(temp->heredoc_delim);
		temp = temp->next;
	}
}

static t_cmd *ft_create_node(t_token *lexicon)
{
	t_cmd 	*new_node;
	int		i = 0;

	new_node = malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	ft_memset(new_node, 0, sizeof(t_cmd));
	if (lexicon && lexicon->type == CMD)
	{
		new_node->args = malloc(sizeof(char *) * 100);
		new_node->args[i++] = ft_strdup(lexicon->value);
		lexicon = lexicon->next;
		while (lexicon && lexicon->type == WORD)
		{
			new_node->args[i++] = ft_strdup(lexicon->value);
			lexicon = lexicon->next;
		}
		new_node->args[i] = NULL;
	}
	while (lexicon)
	{
		if (lexicon->type == INFILE)
			new_node->infile = ft_strdup(lexicon->value);
		else if (lexicon->type == OUTFILE)
			new_node->outfile = ft_strdup(lexicon->value);
		else if (lexicon->type == OUTFILE_APPEND)
		{
			new_node->outfile = ft_strdup(lexicon->value);
			new_node->append = TRUE;
		}
		else if (lexicon->type == HERE_DOC_DELIM)
			new_node->heredoc_delim = ft_strdup(lexicon->value);
		else if (lexicon->type == PIPE)
		{
			new_node->pipe = TRUE;
			break ;
		}
		lexicon = lexicon->next;
	}
	return (new_node);
}

static void	create_exec_list(t_cmd **cmd_list, t_token *lexicon)
{
	t_cmd	*new_node;
	t_cmd	*tail;

	while (lexicon)
	{
		new_node = ft_create_node(lexicon);
		if (!new_node)
			return ;
		if (!*cmd_list)
			*cmd_list = new_node;
		else
			tail->next = new_node;
		tail = new_node;
		while (lexicon && lexicon->type != PIPE)
			lexicon = lexicon->next;
		if (lexicon && lexicon->type == PIPE)
			lexicon = lexicon->next;
	}
}

int exec(t_token *lexicon, char **envp, t_mshell *mshell)
{
	t_cmd	*cmd_list = NULL;
	// t_cmd	*temp;
	// t_token	*temp_lexicon;
	// int		i;
	(void)envp;
	
	// temp_lexicon = lexicon;
	create_exec_list(&cmd_list, lexicon);
	pipeline(cmd_list, envp, mshell);
	// temp = cmd_list;
	// while (temp)
	// {
	// 	i = 0;
	// 	if (temp->args != NULL)
	// 	{
	// 		while (temp->args[i])
	// 		{
	// 			printf("index :%d args: %s \n", i, temp->args[i]);
	// 			i++;
	// 		}
	// 	}
	// 	printf("infile: %s \n outfile: %s \n append: %d \n pipe: %d \n heredoc: %s \n", temp->infile, temp->outfile, temp->append, temp->pipe, temp->heredoc_delim);
	// 	temp = temp->next;
	// }
	free_cmd_list(cmd_list);
	return (1);
}
