/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:42:06 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/07 14:33:47 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

void	exec_export(t_env *env, char *arg)
{
	t_env	*temp;
	char	**args;

	if (!arg)
		return ;
	if (ft_strchr(arg, '=') == NULL)
		return ;
	args = ft_split(arg, '=');
	temp = env;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->key, args[0]) == 0)
		{
			free(temp->value);
			temp->value = ft_strdup(args[1]);
			free_tab(args);
			return ;
		}
		temp = temp->next;
	}
	build_list(&env, args[0], args[1]);
	free(args);
}
