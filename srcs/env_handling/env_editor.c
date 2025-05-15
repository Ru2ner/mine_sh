/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_editor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:35:38 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/15 17:45:50 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

char	*fetch_value_from_env(t_env *env, char *key)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			if (temp->value)
				return (temp->value);
		}
		temp = temp->next;
	}
	return (NULL);
}
