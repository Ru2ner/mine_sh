/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:33:25 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/27 11:27:11 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// static t_bool still_quote(char *input)
// {
// 	int	i;

// 	i = 0;
// 	while (input[i])
// 	{
// 		i++;
// 		if (input[i] == '\'' || input[i] == '\"')
// 			return (TRUE);
// 	}
// 	return (FALSE);
// }

// t_bool	quote_counter(char *input, size_t i)
// {
// 	int			quote_count;
// 	char		quote;

// 	quote_count = 0;
// 	while (input[i] != '\'' && input[i] != '\"')
// 		i++;
// 	if (input[i] == '\'' || input[i] == '\"')
// 	{
// 		quote = input[i];
// 		quote_count++;
// 	}
// 	while (input[i])
// 	{
// 		if (input[i] == quote)
// 		{
// 			quote_count++;
// 			i++;
// 			if (still_quote(input + i) == FALSE)
// 				break ;
// 			while (input[i] != '\'' && input[i] != '\"' && input[i])
// 				i++;
// 			if (input[i] == '\'' || input[i] == '\"')
// 			{
// 				quote = input[i];
// 				quote_count++;
// 			}
// 		}
// 		i++;
// 	}
// 	if ((quote_count % 2) != 0)
// 		return (FALSE);
// 	else
// 		return (TRUE);
// }

t_bool	are_quotes_balanced(char *input)
{
	t_bool	in_single;
	t_bool	in_double;
	size_t	i;

	in_single = 0;
	in_double = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (input[i] == '"' && !in_single)
			in_double = !in_double;
		i++;
	}
	if (in_single == 0 && in_double == 0)
		return (TRUE);
	return (FALSE);
}
