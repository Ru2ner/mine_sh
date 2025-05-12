/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:24:27 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/12 16:53:54 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

t_bool	is_special_char(char c)
{
	if (c == PIPE_CHAR || c == REDIR_IN_CHAR \
		|| c == REDIR_OUT_CHAR)
		return (TRUE);
	return (FALSE);
}

t_bool	is_whitespaces(char c)
{
	if (c == SPACE_CHAR || c == H_TAB || c == V_TAB || c == CARR_RETURN \
		|| c == LINE_FEED || c == FORM_FEED)
		return (TRUE);
	return (FALSE);
}

t_bool	is_quote(char c)
{
	if (c == SINGLE_QUOTE_CHAR || c == DOUBLE_QUOTE_CHAR)
		return (TRUE);
	return (FALSE);
}

t_bool is_builtin(char *str)
{
	if (!str)
		return (FALSE);
	else if (ft_strncmp(str, "echo", 4) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "cd", 2) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "pwd", 3) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "export", 6) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "unset", 5) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "env", 4) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "exit", 4) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "clear", 5) == 0)
		return (TRUE);
	return (FALSE);
}
