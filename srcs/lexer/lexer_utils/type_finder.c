/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:23:58 by tmarion           #+#    #+#             */
/*   Updated: 2025/06/05 16:12:42 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

t_bool	is_pipe(t_token *lexicon)
{
	while (lexicon->next)
	{
		if (lexicon->type == PIPE)
			return (TRUE);
		lexicon = lexicon->next;
	}
	return (FALSE);
}

t_bool	is_redir(t_token *lexicon)
{
	while (lexicon->next)
	{
		if (lexicon->type == REDIR_IN || lexicon->type == REDIR_OUT
			|| lexicon->type == REDIR_OUT_APPEND
			|| lexicon->type == HERE_DOC)
			return (TRUE);
		lexicon = lexicon->next;
	}
	return (FALSE);
}
