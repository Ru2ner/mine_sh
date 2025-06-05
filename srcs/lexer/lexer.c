/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 19:49:34 by tlutz             #+#    #+#             */
/*   Updated: 2025/06/04 20:14:05 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

char	*parse_quoted_string(t_lex_helper *n_tok_content, char **input)
{
	n_tok_content->quote_type = identify_quotes(**input);
	n_tok_content->type = WORD;
	return (extract_quoted_string(input));
}

char	*parse_word(t_lex_helper *n_tok_content, char **input)
{
	n_tok_content->quote_type = NONE;
	n_tok_content->type = WORD;
	return (extract_word(input));
}

char	*parse_special_chars(t_lex_helper *n_tok_content, char **input)
{
	char	*value;

	n_tok_content->quote_type = NONE;
	value = extract_special_char(input);
	n_tok_content->type = identify_special_char(value);
	return (value);
}

void	lexer(char *input, t_token **lexicon)
{
	char			*value;
	t_lex_helper	new_tok_content;

	new_tok_content.linked = TRUE;
	while (*input)
	{
		if (is_whitespaces(*input))
		{
			input++;
			new_tok_content.linked = FALSE;
			continue ;
		}
		else if (is_quote(*input))
			value = parse_quoted_string(&new_tok_content, &input);
		else if (is_special_char(*input))
			value = parse_special_chars(&new_tok_content, &input);
		else
			value = parse_word(&new_tok_content, &input);
		build_lexicon(lexicon, value, &new_tok_content);
		new_tok_content.linked = TRUE;
	}
	identify_redir_file(*lexicon);
}
