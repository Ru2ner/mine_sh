/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:42:13 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/03 19:05:12 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

t_env	*exec_unset(t_env *env, const char *key)
{
	t_env	*temp;
	t_env	*prev;

	temp = env;
	prev = NULL;
	if (temp != NULL && ft_strcmp(temp->key, key) == 0)
	{
		env = temp->next;
		free(temp->key);
		free(temp->value);
		free(temp);
		return (env);
	}
	while (temp != NULL && ft_strcmp(temp->key, key) != 0)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return (env);
	prev->next = temp->next;
	free(temp->key);
	free(temp->value);
	free(temp);
	return (env);
}
