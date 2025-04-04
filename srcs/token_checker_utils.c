/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:24:27 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/04 19:08:54 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	is_special_char(char c)
{
	if (c == PIPE_CHAR || c == REDIR_IN_CHAR \
		|| c == REDIR_OUT_CHAR)
		return (true);
	return (false);
}

bool	is_whitespaces(char c)
{
	if (c == SPACE || c == H_TAB || c == V_TAB || c == CARR_RETURN \
		|| c == LINE_FEED || c == FORM_FEED)
		return (true);
	return (false);
}

bool	is_quote(char c)
{
	if (c == SINGLE_QUOTE_CHAR || c == DOUBLE_QUOTE_CHAR)
		return (true);
	return (false);
}
