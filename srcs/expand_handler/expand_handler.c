/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:41:07 by tmarion           #+#    #+#             */
/*   Updated: 2025/05/20 19:20:20 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

void	expand_handler(t_env *env, char *input)
{
		
}

char	*expand_finder(t_env *env, char *key)
{
	t_env	*temp;
	char	*expanded;

	temp = env;
	if (key[0] == '$')
		key++;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0 && temp->value)
		{
			expanded = ft_strdup(temp->value);
			if (!expanded)
				return (malloc_error());
			return (expanded);
		}
		temp = temp->next;
	}
	expanded = ft_strdup(key);
	if (!expanded)
		return (malloc_error());
	return (key);
}
