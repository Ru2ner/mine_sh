/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:33:25 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/27 14:11:44 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_bool still_quote(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	quote_counter(char *input, size_t i)
{
	int			quote_count;
	char		quote;

	quote_count = 0;
	if (!input)
		return (TRUE);
	while (input[i] && input[i] != '\'' && input[i] != '\"')
		i++;
	if (input[i] == '\'' || input[i] == '\"')
		quote = input[i];
	while (input[i])
	{
		if (input[i] == quote)
		{
			i++;
			quote_count++;
			if (still_quote(input + i) == FALSE)
				return (FALSE);
			while (input[i] != '\'' && input[i] != '\"' && input[i])
				i++;
			if (input[i] == '\'' || input[i] == '\"')
			{
				quote = input[i];
				quote_count++;
			}
		}
		i++;
	}
	printf("count: %d\n\n", quote_count);
	if ((quote_count % 2) != 0)
		return (FALSE);
	else
		return (TRUE);
}
