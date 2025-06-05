/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:12:12 by tmarion           #+#    #+#             */
/*   Updated: 2025/06/05 20:25:09 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include "parsing.h"
#include <signal.h>

static int	malloc_size(t_token *lex)
{
	t_token	*tmp;
	int		count;

	count = 0;
	if (!lex)
		return (count);
	tmp = lex;
	while (tmp)
	{
		if (tmp->type == WORD)
			count++;
		if (tmp->type == PIPE)
			break ;
		tmp = tmp->next;
	}
	return (count);
}

static char	*join_link_args(t_token **lex)
{
	char	*tmp;
	char	*joined;
	t_token	*current;

	if (!lex || !*lex || !(*lex)->next)
		return (NULL);
	tmp = ft_strjoin((*lex)->value, (*lex)->next->value);
	if (!tmp)
		return (NULL);
	*lex = (*lex)->next;
	current = *lex;
	while (current && current->next && current->next->linked == TRUE)
	{
		joined = ft_strjoin(tmp, current->next->value);
		free(tmp);
		if (!joined)
			return (NULL);
		tmp = joined;
		current = current->next;
		*lex = current;
	}
	return (tmp);
}

static void	handle_args(t_cmd *node, t_token *lex)
{
	int		i;

	i = 0;
	node->args = malloc(sizeof(char *) * (malloc_size(lex) + 1));
	while (lex)
	{
		if (lex->type == INFILE)
			node->infile = ft_strdup(lex->value);
		else if (lex->type == OUTFILE)
			node->outfile = ft_strdup(lex->value);
		else if (lex->type == REDIR_OUT_APPEND)
			node->append = TRUE;
		else if (lex->type == PIPE)
		{
			node->pipe = TRUE;
			lex = lex->next;
			break ;
		}
		else if (lex->type == HERE_DOC_DELIM)
			node->heredoc_delim = ft_strdup(lex->value);
		else if (lex->type == WORD)
		{
			if (lex->next && lex->next->linked == TRUE)
				node->args[i] = join_link_args(&lex);
			else
				node->args[i] = ft_strdup(lex->value);
			i++;
		}
		lex = lex->next;
	}
	node->args[i++] = NULL;
}

t_cmd	*ft_create_node(t_token **lexicon, t_env *env)
{
	t_cmd	*new_node;

	(void)env;
	new_node = malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	ft_memset(new_node, 0, sizeof(t_cmd));
	handle_args(new_node, *lexicon);
	return (new_node);
}
