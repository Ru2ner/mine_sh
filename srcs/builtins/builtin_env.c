/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:42:01 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/08 17:56:50 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

void	print_env(t_env *env)
{
	if (!env)
		return ;
	while (env)
	{
		if (env->env == true)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
