/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:42:13 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/24 12:42:04 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

static	void	destroy_node(t_env *temp)
{
	if (!temp)
		return ;
	if (temp->key)
		free(temp->key);
	if (temp->value)
		free(temp->value);
	if (temp)
		free(temp);
}

t_env	*unset(t_env *env, const char *key)
{
	t_env	*temp;
	t_env	*prev;

	temp = env;
	prev = NULL;
	if (!key)
		return (env);
	if (temp != NULL && ft_strcmp(temp->key, key) == 0)
	{
		env = temp->next;
		destroy_node(temp);
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
	destroy_node(temp);
	return (env);
}
