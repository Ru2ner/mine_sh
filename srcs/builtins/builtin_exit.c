/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:41:28 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/21 20:13:46 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_bool	is_arg_number(const char *arg)
{
	if (!arg || *arg)
		return (FALSE);
	if (*arg == '-' || *arg == '+')
		arg++;
	if (!*arg)
		return (FALSE);
	while (*arg)
	{
		if (*arg < '0' || *arg > '9')
			return (FALSE);
		arg++;
	}
	return (TRUE);
}
