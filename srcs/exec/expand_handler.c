/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 19:49:30 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/04 20:18:02 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

void	expand_handler(t_env *env, const char *token_value)
{
	if (token_value[0] == '$')
		token_value++;
	while (env)
	{
		if (ft_strlen(env->key) > 1 && ft_strcmp(env->key, token_value))
			
			
	}
}
