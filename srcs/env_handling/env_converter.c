/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_converter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:59:07 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/09 19:38:35 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

//TODO Maybe passer les fonctions en void * pour avoir un retour en cas de malloc fail.
void	*convert_env_to_list(char **envp, t_env **env)
{
	char	**converted_array;
	char	*key;
	char	*value;
	int		i;

	i = 0;
	while (envp[i])
	{
		converted_array = ft_split(envp[i], '=');
		if (!converted_array)
			return (NULL);
		if (converted_array && converted_array[0] && converted_array[1])
		{
			key = ft_strdup(converted_array[0]);
			if (!key)
				return (NULL);
			value = ft_strdup(converted_array[1]);
			if (!value)
				return (NULL);
			build_list(env, key, value, true);
		}
		free_tab(converted_array);
		i++;
	}
	return (NULL);
}

char	**convert_env_to_tab(t_env *env)
{
	char	**result;
	size_t	i;
	size_t	list_size;

	i = 0;
	list_size = get_list_size(env);
	result = malloc(sizeof(char *) * (list_size + 1));
	if (!result)
		return (NULL);
	while (i < list_size)
	{
		result[i] = ft_strcjoin(env->key, env->value, '=');
		if (!result[i])
			return (free_dest(result, i - 1));
		env = env->next;
		i++;
	}
	result[i] = NULL;
	return (result);
}
