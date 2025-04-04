/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_quoted_string.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:45:00 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/04 17:50:13 by tlutz            ###   ########.fr       */
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
