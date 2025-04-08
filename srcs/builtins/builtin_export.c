/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:42:06 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/08 20:30:23 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

//TODO Handling du += WIP, need split avec charset.
//TODO Les arguments envoyés à export doivent être parsé, lettres et underscore au début seulement
static void	*add_to_export_list(t_env *env, char *arg)
{
	while (env)
	{
		build_list(&env, arg, "", false);
		env = env->next;
	}
	return (NULL);
}

static void	*print_export(t_env *env)
{
	while (env)
	{
		if (env->export == false)//TODO le false est là uniquement pour les tests, à modifier
		printf("export %s=\"%s\"\n", env->key, env->value);
		env = env->next;
	}
	return (NULL);
}

void	*exec_export(t_env *env, char *arg)
{
	t_env	*temp;
	char	**args;

	if (!arg)
		return (print_export(env));
	if (ft_strchr(arg, '=') == NULL)
		return (add_to_export_list(env, arg));
	args = ft_split(arg, '=');
	temp = env;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->key, args[0]) == 0)
		{
			free(temp->value);
			temp->value = ft_strdup(args[1]);
			free_tab(args);
			return (NULL);
		}
		temp = temp->next;
	}
	build_list(&env, args[0], args[1], true);
	free(args);
	return (NULL);
}
