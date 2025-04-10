/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:13:28 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/10 20:04:04 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

void	*add_to_export_list(t_env **env, char *arg)
{
	t_keyval	key_value;

	key_value.key = ft_strdup(arg);
	key_value.value = NULL;
	build_list(env, &key_value, false, true);
	return (NULL);
}

void	*print_export(t_env *env)
{
	while (env)
	{
		if (env->export == true)
		{
			if (env->key && env->value)
				printf("export %s=\"%s\"\n", env->key, env->value);
			else if (env->key && !env->value)
				printf("export %s\n", env->key);
		}
		env = env->next;
	}
	return (NULL);
}
