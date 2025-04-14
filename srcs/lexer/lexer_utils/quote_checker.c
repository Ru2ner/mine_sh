/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:33:25 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/14 15:37:20 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_bool	quote_counter(char *input)
{
	size_t	i;
	int		dquote_count;
	int		squote_count;

	i = 0;
	dquote_count = 0;
	squote_count = 0;
	while (input[i])
	{
		if (input[i] == '\"')
			dquote_count++;
		if (input[i] == '\'')
			squote_count++;
		i++;
	}
	if (dquote_count % 2 == 0 && squote_count % 2 == 0)
		return (true);
	return (false);
}
