/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:41:07 by tmarion           #+#    #+#             */
/*   Updated: 2025/05/12 16:44:13 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

char	*expand_handler(t_env *env, char *key)
{
	t_env	*temp;
	char	*expanded;

	temp = env;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			expanded = ft_strdup(temp->value);
			if (!expanded)
				return (malloc_error());
			return (expanded);
		}
		temp = temp->next;
	}
	return (NULL);
}
