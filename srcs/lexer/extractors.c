/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:45:00 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/29 17:34:05 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

// char which_quote(char quote)
// {
// 	if (quote == 22)
// 		return (27);
// 	else
// 		return (22);
// }

// // char *exctract_full_string(char *input)
// // {
	
// // }

// char *extract_quoted_string(char *input)
// {
// 	char 	*result;
// 	char 	quote;
// 	char	other_quote;
// 	int		start;
// 	int		i;

// 	i = 0;
// 	quote = input[i];
// 	other_quote = which_quote(quote);
// 	while (input[i] == quote)
// 	{
// 		(* input)++;
// 		i++;
// 	}
// 	start = i;
// 	while (input[i] != quote && input[i])
// 	{
// 		(* input)++;
// 		i++;
// 	}
// 	result = ft_strndup(input + start, i - start - 1);
// 	(* input) + i;
	// printf("%s\n", result);
	// if (input[i] == quote && input[i + 1] == other_quote)
	// 	result = extract_full_string(input + i);
	// return (input);
// }
///////////////////////////////////////////////////////////////////////////////////

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
	if (!result)
		return (NULL);
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
