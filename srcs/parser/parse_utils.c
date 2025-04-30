/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:40:48 by tmarion           #+#    #+#             */
/*   Updated: 2025/04/29 13:43:45 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

static t_bool valid_redir(t_token *lexicon)
{
	if (!lexicon->value)
		lexicon = lexicon->next;
	if (lexicon->type == PIPE || lexicon->type == REDIR_IN || lexicon->type == REDIR_OUT)
		return (false);
	
	while (lexicon->next)
	{
		if (lexicon->type == PIPE && lexicon->next->type != CMD)
			return (false);
		lexicon = lexicon->next;
	}
	
	if (lexicon->type == PIPE || lexicon->type == REDIR_IN || lexicon->type == REDIR_OUT)
		return (false);
	return (true);
}


t_bool parsing_input(t_token *lexicon)
{
	if (valid_redir(lexicon))
		return (true);
	return (false);
}