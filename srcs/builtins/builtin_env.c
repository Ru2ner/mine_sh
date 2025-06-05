/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:42:01 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/29 17:56:04 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

int	print_env(t_env *env)
{
	if (!env)
		return (1);
	while (env)
	{
		if (env->env == TRUE)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
