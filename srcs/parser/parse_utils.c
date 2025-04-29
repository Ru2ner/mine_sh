/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:40:48 by tmarion           #+#    #+#             */
/*   Updated: 2025/04/29 11:53:56 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

t_bool valid_redir(t_token *lexicon)
{
	if (!lexicon->value)
		lexicon = lexicon->next;
	if (lexicon->value == PIPE || lexicon->value == REDIR_IN || lexicon->value == REDIR_OUT)
		return (false);
	while (lexicon->next)
		lexicon = lexicon->next;
	if (lexicon->value == PIPE || lexicon->value == REDIR_IN || lexicon->value == REDIR_OUT)
		return (false);
	return (true);
}


t_bool parsing(t_token *lexicon)
{
	if (valid_redir(lexicon))
		return (true);
}