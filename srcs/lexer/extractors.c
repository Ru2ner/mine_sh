/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:45:00 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/30 12:35:51 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

static int	is_linked_quote_string(char *input)
{
	int	i;
	int	count;

	printf("input: %s\n", input);
	count = -2;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			count++;
		if (input[i] == ' ')
			return (0);
		i++;
	}
	return (count);
}

char	*extract_quoted_string(char *input)
{
	char	*result;
	char	quote;
	int		start;
	int		i;
	int		link = is_linked_quote_string(input) / 2;

	printf("link: %d\n", link);
	i = 0;
	if (!input)
		return (NULL);
	quote = input[i];
	i++;
	start = i;
	while (input[i] && input[i] != quote)
		i++;
	result = ft_strndup(input + start, i - start);
	if (!result)
		return (NULL);
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
