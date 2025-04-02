/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:01:40 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/02 19:02:24 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_list(t_env *env)
{
	t_env	*temp;

	if (!env)
		return ;
	while (env)
	{
		temp = env;
		env = env->next;
		free(temp->var);
		free(temp->value);
		free(temp);
	}
}

size_t	get_list_size(t_env *env)
{
	size_t	i;

	i = 0;
	if (!env)
		return (0);
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

t_env	*create_new_node(char *var, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->var = var;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	build_list(t_env **env, char *var, char *value)
{
	t_env	*new_node;
	t_env	*temp;

	new_node = create_new_node(var, value);
	temp = *env;
	if (!new_node)
		return ;//TODO handle_close, exit et free à rajouter au plus vite
	if (!*env)
	{
		*env = new_node;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
}
