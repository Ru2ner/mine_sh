/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:23:58 by tmarion           #+#    #+#             */
/*   Updated: 2025/04/29 16:33:08 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

t_bool	is_pipe(t_token *lexicon)
{
	while (lexicon->next)
	{
		if (lexicon->type == PIPE)
			return (true);
		lexicon = lexicon->next;
	}
	return (false);
}

t_bool	is_redir(t_token *lexicon)
{
	while (lexicon->next)
	{
		if (lexicon->type == REDIR_IN || lexicon->type == REDIR_OUT
				|| lexicon->type == REDIR_OUT_APPEND)
			return (true);
		lexicon = lexicon->next;
	}
	return (false);
}
