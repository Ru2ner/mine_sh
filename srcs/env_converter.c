/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_converter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:59:07 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/02 19:03:22 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

void	convert_env_to_list(char **envp, t_env **env)
{
	char	**converted_array;
	int		i;
	
	i = 0;
	while (envp[i])
	{
		converted_array = ft_split(envp[i], '=');
		if (converted_array && converted_array[0] && converted_array[1])
		{
			build_list(env, ft_strdup(converted_array[0]), \
			ft_strdup(converted_array[1]));
		}
		free_tab(converted_array);
		i++;
	}
}
