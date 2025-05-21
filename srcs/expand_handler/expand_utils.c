/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:06:58 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/21 13:43:28 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

t_bool	is_valid_for_env_var(char *key)
{
	size_t	i;

	i = 0;
	if (ft_isdigit(key[0]))
		return (FALSE);
	while (key[i])
	{
		if (!ft_isalnum(key[i]) || key[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}
