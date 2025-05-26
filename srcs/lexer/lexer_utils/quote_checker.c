/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:33:25 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/26 18:34:42 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_bool still_quote(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		i++;
		if (input[i] == '\'' || input[i] == '\"')
			return (TRUE);
	}
	return (FALSE);
}

t_bool	quote_counter(char *input, size_t i)
{
	int			quote_count;
	char		quote;

	quote_count = 0;
	while (input[i] != '\'' && input[i] != '\"')
		i++;
	if (input[i] == '\'' || input[i] == '\"')
	{
		quote = input[i];
		quote_count++;
	}
	while (input[i])
	{
		if (input[i] == quote)
		{
			quote_count++;
			i++;
			if (still_quote(input + i) == FALSE)
				break ;
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
	if ((quote_count % 2) != 0)
		return (FALSE);
	else
		return (TRUE);
}
