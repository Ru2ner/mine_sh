/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 19:49:34 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/14 19:57:40 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	lexer(const char *input, const char **lexicon)
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
			quote_type = indentify_quotes(*input);
			
		}
	}

}
