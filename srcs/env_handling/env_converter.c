/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_converter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:59:07 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/28 20:08:09 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

//TODO Fonction en void * pour retour si malloc fail.
void	*convert_env_to_list(char **envp, t_env **env)
{
	char		**converted_array;
	t_keyval	key_value;
	int			i;

	i = 0;
	while (envp[i])
	{
		converted_array = ft_split(envp[i], '=');
		if (!converted_array)
			return (malloc_error());
		if (converted_array && converted_array[0] && converted_array[1])
		{
			key_value.key = ft_strdup(converted_array[0]);
			if (!key_value.key)
				return (malloc_error());
			key_value.value = ft_strdup(converted_array[1]);
			if (!key_value.value)
				return (malloc_error());
			build_list(env, &key_value, TRUE, TRUE);
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
		return (malloc_error());
	while (i < list_size)
	{
		if (env->key && env->value)
			result[i] = ft_strcjoin(env->key, env->value, '=');
		if (!result[i])
			return (free_dest(result, i - 1));
		env = env->next;
		i++;
	}
	result[i] = NULL;
	return (result);
}
