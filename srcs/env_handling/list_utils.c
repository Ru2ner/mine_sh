/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:01:40 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/14 14:09:39 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

void	free_list(t_env *env)
{
	t_env	*temp;

	if (!env)
		return ;
	while (env)
	{
		temp = env;
		env = env->next;
		if (temp->key)
			free(temp->key);
		if (temp->value)
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

t_env	*create_new_node(char *var, char *value, t_bool print, t_bool export)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (malloc_error());
	ft_memset(node, 0, sizeof(t_env));
	node->key = ft_strdup(var);
	if (!node->key)
		return (malloc_error());
	if (value)
	{
		node->value = ft_strdup(value);
		if (!node->value)
			return (malloc_error());
	}
	else
		node->value = NULL;
	node->env = print;
	node->export = export;
	node->next = NULL;
	if (var)
		free(var);
	if (value)
		free(value);
	return (node);
}
//TODO handle_close, exit et free à rajouter au plus vite

void	build_list(t_env **env, t_keyval *key_val, t_bool print, t_bool export)
{
	t_env	*new_node;
	t_env	*temp;

	new_node = create_new_node(key_val->key, key_val->value, print, export);
	if (!new_node)
		return ;
	if (!*env)
	{
		*env = new_node;
		return ;
	}
	temp = *env;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
}
