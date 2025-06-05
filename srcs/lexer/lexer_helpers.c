/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 20:02:42 by tlutz             #+#    #+#             */
/*   Updated: 2025/06/05 16:11:35 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

t_quote_type	identify_quotes(const char c)
{
	if (c == SINGLE_QUOTE_CHAR)
		return (SINGLE);
	else if (c == DOUBLE_QUOTE_CHAR)
		return (DOUBLE);
	return (NONE);
}

t_token_type	identify_special_char(const char *input)
{
	if (ft_strcmp(input, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(input, "<") == 0)
		return (REDIR_IN);
	else if (ft_strcmp(input, ">") == 0)
		return (REDIR_OUT);
	else if (ft_strcmp(input, "<<") == 0)
		return (HERE_DOC);
	else if (ft_strcmp(input, ">>") == 0)
		return (REDIR_OUT_APPEND);
	return (WORD);
}

void	identify_redir_file(t_token *lexicon)
{
	while (lexicon && lexicon->next)
	{
		if (lexicon->type == HERE_DOC)
			lexicon->next->type = HERE_DOC_DELIM;
		else if (lexicon->type == REDIR_IN)
			lexicon->next->type = INFILE;
		else if (lexicon->type == REDIR_OUT)
			lexicon->next->type = OUTFILE;
		else if (lexicon->type == REDIR_OUT_APPEND)
			lexicon->next->type = OUTFILE_APPEND;
		lexicon = lexicon->next;
	}
}
