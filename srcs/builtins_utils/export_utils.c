/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:13:28 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/10 19:15:35 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	*add_to_export_list(t_env *env, char *arg)
{
	t_keyval key_value;
	
	key_value.key = arg;
	key_value.value = "";
	while (env)
	{
		build_list(&env, &key_value, false, true);
		env = env->next;
	}
	return (NULL);
}

void	*print_export(t_env *env)
{
	while (env)
	{
		if (env->export == true)
			printf("export %s=\"%s\"\n", env->key, env->value);
		env = env->next;
	}
	return (NULL);
}
