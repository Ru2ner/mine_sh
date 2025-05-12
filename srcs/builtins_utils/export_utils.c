/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:13:28 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/07 13:35:35 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

void	*add_to_export_list(t_env **env, char *arg)
{
	t_keyval	key_value;
	t_env		*temp;

	temp = *env;
	while (temp)
	{
		if (ft_strcmp(arg, temp->key) == 0)
			return (NULL);
		temp = temp->next;
	}
	key_value.key = ft_strdup(arg);
	key_value.value = NULL;
	build_list(env, &key_value, FALSE, TRUE);
	return (NULL);
}

static t_env	*copy_env_list(t_env *og)
{
	t_env		*copy;
	t_env		*temp;
	t_keyval	keyval;

	copy = NULL;
	temp = og;
	while (temp)
	{
		keyval.key = ft_strdup(temp->key);
		if (!keyval.key)
			return (malloc_error());
		if (temp->value)
		{
			keyval.value = ft_strdup(temp->value);
			if (!keyval.key)
				return (malloc_error());
		}
		else
			keyval.value = NULL;
		build_list(&copy, &keyval, temp->env, temp->export);
		temp = temp->next;
	}
	return (copy);
}

static void	swap_nodes(t_env *node1, t_env *node2)
{
	char	*temp_key;
	char	*temp_value;
	t_bool	temp_env;
	t_bool	temp_export;

	temp_key = node1->key;
	node1->key = node2->key;
	node2->key = temp_key;
	temp_value = node1->value;
	node1->value = node2->value;
	node2->value = temp_value;
	temp_env = node1->env;
	node1->env = node2->env;
	node2->env = temp_env;
	temp_export = node1->export;
	node1->export = node2->export;
	node2->export = temp_export;
}

static void	sort_env_list(t_env **head)
{
	t_env	*temp;
	int		swapped;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		temp = *head;
		while (temp && temp->next)
		{
			if (ft_strcmp(temp->key, temp->next->key) > 0)
			{
				swap_nodes(temp, temp->next);
				swapped = 1;
			}
			temp = temp->next;
		}
	}
}

void	*print_export(t_env *env)
{
	t_env	*temp;
	t_env	*copy;

	copy = copy_env_list(env);
	sort_env_list(&copy);
	temp = copy;
	while (temp)
	{
		if (temp->export == TRUE)
		{
			if (temp->key && temp->value)
				printf("export %s=\"%s\"\n", temp->key, temp->value);
			else if (temp->key && !temp->value)
				printf("export %s\n", temp->key);
		}
		temp = temp->next;
	}
	free_list(copy);
	return (NULL);
}
