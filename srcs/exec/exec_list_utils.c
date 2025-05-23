/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:19:59 by tmarion           #+#    #+#             */
/*   Updated: 2025/05/23 13:40:01 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include "parsing.h"
#include <signal.h>

static void	skip_redir(t_token **lexicon)
{
	while (*lexicon && ((*lexicon)->type == REDIR_IN
			|| (*lexicon)->type == REDIR_OUT
			|| (*lexicon)->type == REDIR_OUT_APPEND
			|| (*lexicon)->type == HERE_DOC))
		*lexicon = (*lexicon)->next;
}

static void	handle_args(t_cmd *node, t_token *lexicon)
{
	int		i;
	char	*tmp;
	t_token	*tmp_token;
	
	i = 0;
	tmp_token = lexicon;
	node->args = malloc(sizeof(char *) * 100);
	while (tmp_token && tmp_token->type == WORD)
	{
		if (tmp_token->next && tmp_token->next->link == TRUE)
		{
			tmp = ft_strjoin(tmp_token->value, tmp_token->next->value);
			tmp_token = tmp_token->next;
			while (tmp_token->next && tmp_token->next->value
				&& tmp_token->next->link == TRUE)
			{
				tmp = ft_strjoin(tmp, tmp_token->next->value);
				tmp_token = tmp_token->next;
			}
			node->args[i++] = tmp;
		}
		else
			node->args[i++] = ft_strdup(tmp_token->value);
		tmp_token = tmp_token->next;
	}
	node->args[i] = NULL;
}

static void	findin_fd(t_cmd *node, t_token **lexicon)
{
	while (*lexicon && ((*lexicon)->type == INFILE
			|| (*lexicon)->type == OUTFILE
			|| (*lexicon)->type == OUTFILE_APPEND
			|| (*lexicon)->type == HERE_DOC_DELIM))
	{
		if ((*lexicon)->type == INFILE)
			node->infile = ft_strdup((*lexicon)->value);
		else if ((*lexicon)->type == OUTFILE)
			node->outfile = ft_strdup((*lexicon)->value);
		else if ((*lexicon)->type == OUTFILE_APPEND)
		{
			node->outfile = ft_strdup((*lexicon)->value);
			node->append = TRUE;
		}
		else if ((*lexicon)->type == HERE_DOC_DELIM)
			node->heredoc_delim = ft_strdup((*lexicon)->value);
		*lexicon = (*lexicon)->next;
	}
}
static void	findout_fd(t_cmd *node, t_token *lexicon)
{
	while (lexicon)
	{
		if (lexicon->type == INFILE)
			node->infile = ft_strdup(lexicon->value);
		else if (lexicon->type == OUTFILE)
			node->outfile = ft_strdup(lexicon->value);
		else if (lexicon->type == OUTFILE_APPEND)
		{
			node->outfile = ft_strdup(lexicon->value);
			node->append = TRUE;
		}
		else if (lexicon->type == HERE_DOC_DELIM)
			node->heredoc_delim = ft_strdup(lexicon->value);
		else if (lexicon->type == PIPE)
		{
			node->pipe = TRUE;
			break ;
		}
		lexicon = lexicon->next;
	}
}

t_cmd	*ft_create_node(t_token **lexicon, t_env *env)
{
	t_cmd	*new_node;

	(void)env;
	new_node = malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	ft_memset(new_node, 0, sizeof(t_cmd));
	skip_redir(lexicon);
	findin_fd(new_node, lexicon);
	handle_args(new_node, *lexicon);
	findout_fd(new_node, *lexicon);
	return (new_node);
}
