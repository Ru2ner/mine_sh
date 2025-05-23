/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list_creator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:08:09 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/23 16:06:42 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include <signal.h>

static void	create_exec_list(t_cmd **cmd_list, t_token *lexicon, t_env *env)
{
	t_cmd	*new_node;
	t_cmd	*tail;

	while (lexicon)
	{
		new_node = ft_create_node(lexicon, env);
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
	
	create_exec_list(&cmd_list, lexicon, mshell->env);
	//
		// int		i;
		// printf("------------------Exec List--------------------------------------\n");
		// t_cmd	*temp;
		// temp = cmd_list;
		// i = 0;
		// while (temp)
		// {
		// 	i = 0;
		// 	if (temp->args != NULL)
		// 	{
		// 		while (temp->args[i])
		// 		{
		// 			printf("args: %s \n", temp->args[i]);
		// 			i++;
		// 		}
		// 	}
		// 	printf("infile: %s \n outfile: %s \n append: %d \n pipe: %d \n heredoc: %s \n", temp->infile, temp->outfile, temp->append, temp->pipe, temp->heredoc_delim);
		// 	temp = temp->next;
		// }
	//
	pipeline(cmd_list, envp, mshell, lexicon);
	free_cmd_list(cmd_list);
	return (1);
}


////////////////////////////////////////////////////////////////////////

// static t_cmd *ft_create_node(t_token *lexicon, t_env *env)
// {
// 	t_cmd 	*new_node;
// 	char	*temp_string;
// 	t_token	*temp;
// 	int		i = 0;
// 	(void)env;

// 	new_node = malloc(sizeof(t_cmd));
// 	if (!new_node)
// 		return (NULL);
// 	ft_memset(new_node, 0, sizeof(t_cmd));
// 	//EXPAND HANDLER --> MODIF LEXICON
// 	while (lexicon && (lexicon->type == REDIR_IN || lexicon->type == REDIR_OUT \
// 		|| lexicon->type == REDIR_OUT_APPEND || lexicon->type == HERE_DOC))
// 		lexicon = lexicon->next;
// 	while (lexicon && (lexicon->type == INFILE || lexicon->type == OUTFILE \
// 		|| lexicon->type == OUTFILE_APPEND || lexicon->type == HERE_DOC_DELIM))
// 	{
// 		if (lexicon->type == INFILE)
// 			new_node->infile = ft_strdup(lexicon->value);
// 		else if (lexicon->type == OUTFILE)
// 			new_node->outfile = ft_strdup(lexicon->value);
// 		else if (lexicon->type == OUTFILE_APPEND)
// 		{
// 			new_node->outfile = ft_strdup(lexicon->value);
// 			new_node->append = TRUE;
// 		}
// 		else if (lexicon->type == HERE_DOC_DELIM)
// 			new_node->heredoc_delim = ft_strdup(lexicon->value);
// 		lexicon = lexicon->next;
// 	}
// 	//

	
// 	temp = lexicon;
// 	new_node->args = malloc(sizeof(char *) * 100); //TODO Compter le nombre d'arguments pour malloc
// 	while (temp && temp->type == WORD)
// 	{
// 		if (temp->next && temp->next->link == TRUE)
// 		{
// 			temp_string = ft_strjoin(temp->value, temp->next->value);
// 			temp = temp->next;
// 			while (temp->next && temp->next->value && temp->next->link == TRUE)
// 			{
// 				temp_string = ft_strjoin(temp_string, temp->next->value);
// 				temp = temp->next;
// 			}
// 			new_node->args[i++] = temp_string;
// 		}
// 		else
// 			new_node->args[i++] = ft_strdup(temp->value);
// 		temp = temp->next;
// 	}
// 	new_node->args[i] = NULL;


// 	while (lexicon)
// 	{
// 		if (lexicon->type == INFILE)
// 			new_node->infile = ft_strdup(lexicon->value);
// 		else if (lexicon->type == OUTFILE)
// 			new_node->outfile = ft_strdup(lexicon->value);
// 		else if (lexicon->type == OUTFILE_APPEND)
// 		{
// 			new_node->outfile = ft_strdup(lexicon->value);
// 			new_node->append = TRUE;
// 		}
// 		else if (lexicon->type == HERE_DOC_DELIM)
// 			new_node->heredoc_delim = ft_strdup(lexicon->value);
// 		else if (lexicon->type == PIPE)
// 		{
// 			new_node->pipe = TRUE;
// 			break ;
// 		}
// 		lexicon = lexicon->next;
// 	}
// 	return (new_node);
// }
///////////////////////////////////////