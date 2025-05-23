/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:21:37 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/23 16:35:22 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

char	*create_prompt(t_env *env)
{
	t_env	*temp;
	char	*prompt;

	temp = env;
	while (temp)
	{
		if (ft_strcmp(temp->key, "PWD") == 0)
		{
			if (temp->value)
			{
				prompt = ft_strjoin(temp->value, " $ ");
				
				if (!prompt)
					return (malloc_error());
				return (prompt);
			}
		}
		temp = temp->next;
	}
	return (PROMPT);
}
