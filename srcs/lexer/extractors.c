/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:45:00 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/20 16:55:32 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

// static int	is_linked_quote_string(char *input)
// {
// 	int	i;
// 	int	count;

// 	// printf("input: %s\n", input);
// 	count = -2;
// 	i = 0;
// 	while (input[i])
// 	{
// 		if (input[i] == '\'' || input[i] == '\"')
// 			count++;
// 		if (input[i] == ' ')
// 			return (0);
// 		i++;
// 	}
// 	return (count);
// }

char	*extract_quoted_string(char **input)
{
	char	*result;
	char	quote;
	int		start;
	int		i;

	i = 0;
	if (!input)
		return (NULL);
	quote = (*input)[i];
	i++;
	start = i;
	while ((*input)[i] && (*input)[i] != quote)
		i++;
	result = ft_strndup(*input + start, i - start);
	if (!result)
		return (malloc_error());
	if ((*input)[i] == quote)
		i++;
	*input += i;
	return (result);
}

char	*extract_word(char **input)
{
	const char *start = *input;
	char				*value;

	while (**input && !is_whitespaces(**input) && !is_special_char(**input) && **input != '\'' && **input != '\"')
		(*input)++;
	value = ft_strndup(start, *input - start);
	if (!value)
		return (malloc_error());
	return (value);
}

char	*extract_special_char(char **input)
{
	char	*value;
	
	if (**input == REDIR_IN_CHAR && *(*input + 1) == REDIR_IN_CHAR)
	{
		(*input) += 2;
		value = ft_strdup("<<");
		if (!value)
			return (malloc_error());
		return (value);
	}
	else if (**input == REDIR_OUT_CHAR && *(*input + 1) == REDIR_OUT_CHAR)
	{
		(*input) += 2;
		value = ft_strdup(">>");
		if (!value)
			return (malloc_error());
		return (value);
	}	
	else
	{
		value = ft_strndup((*input)++, 1);
		if (!value)
			return (malloc_error());
		return (value);
	}
}
