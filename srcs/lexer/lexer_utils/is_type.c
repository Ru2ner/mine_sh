/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:23:58 by tmarion           #+#    #+#             */
/*   Updated: 2025/05/12 16:19:06 by tlutz            ###   ########.fr       */
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
				|| lexicon->type == REDIR_OUT_APPEND)
			return (TRUE);
		lexicon = lexicon->next;
	}
	return (FALSE);
}
