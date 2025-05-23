/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:40:48 by tmarion           #+#    #+#             */
/*   Updated: 2025/05/23 16:43:17 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

static t_bool valid_redir(t_token *lexicon)
{
	if (!lexicon->value)
		lexicon = lexicon->next;
	if (lexicon->type == PIPE)
		return (FALSE);
	
	while (lexicon->next)
	{
		if (lexicon->type == PIPE && lexicon->next->type != WORD)
			return (FALSE);
		lexicon = lexicon->next;
	}
	
	if (lexicon->type == PIPE || lexicon->type == REDIR_IN || lexicon->type == REDIR_OUT)
		return (FALSE);
	return (TRUE);
}

void find_redir(t_token *lexicon)
{
	while (lexicon->next)
	{
		if (lexicon->type == REDIR_OUT)
			lexicon->next->type = OUTFILE;
		lexicon = lexicon->next;
	}
}


t_bool parsing_input(t_token *lexicon)
{
	if (!lexicon)
		return (TRUE);
	if (valid_redir(lexicon))
	{
		find_redir(lexicon);
		return (TRUE);
	}
	return (FALSE);
}