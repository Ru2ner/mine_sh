/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 19:49:34 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/15 15:51:44 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

static t_quote_type	identify_quotes(const char c)
{
	if (c == SINGLE_QUOTE_CHAR)
		return (SINGLE);
	else if (c == DOUBLE_QUOTE_CHAR)
		return (DOUBLE);
	return (NONE);
}

static t_token_type	identify_special_char(const char *input)
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

void	lexer(char *input, t_token **lexicon)
{
	t_token_type	type;
	t_quote_type	quote_type;
	char			*value;
	
	while (*input)
	{
		if (is_whitespaces(*input))
		{
			input++;
			continue ;
		}
		else if (is_quote(*input))
		{
			quote_type = identify_quotes(*input);
			type = WORD;
			value = extract_quoted_string(&input);
		}
		else if (is_special_char(*input))
	{
			quote_type = NONE;
			value = extract_special_char(&input);
			type = identify_special_char(value);
		}
		else
		{
			quote_type = NONE;
			type = WORD;
			value = extract_word(&input);
		}
		build_lexicon(lexicon, value, type, quote_type);
	}
	identify_redir_file(*lexicon);
}
