/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:45:00 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/04 19:45:57 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

char	*extract_quoted_string(char **input)
{
	char	*result;
	char	quote;
	char	*start;

	quote = **input;
	(*input)++;
	start = *input;
	while (**input && **input != quote)
		(*input)++;
	result = ft_strndup(start, *input - start);
	if (**input == quote)
		(*input)++;
	return (result);
}

char	*extract_word(const char **input)
{
	const char *start = *input;

	while (**input && !is_whitespaces(**input) && !is_special_char(**input))
		(*input)++;
	return (ft_strndup(start, *input - start));
}

char	*extract_special_char(const char **input)
{
	if (**input == REDIR_IN_CHAR && *(*input + 1) == REDIR_IN_CHAR)
	{
		(*input) += 2;
		return (ft_strdup("<<"));
	}
	else if (**input == REDIR_OUT_CHAR && *(*input + 1) == REDIR_OUT_CHAR)
	{
		(*input) += 2;
		return (ft_strdup(">>"));
	}	
	else
		return (ft_strndup((*input)++, 1));
}
