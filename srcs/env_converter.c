/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_converter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:59:07 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/08 17:58:52 by tlutz            ###   ########.fr       */
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
			ft_strdup(converted_array[1]), true);
		}
		free_tab(converted_array);
		i++;
	}
}

// char	**convert_env_to_tab(t_env **env)
// {
// 	char	**result;
// 	char	*tmp;
// 	size_t	i;
// 	size_t	list_size;
// 	t_env	*temp;

// 	i = 0;
// 	temp = *env;
// 	list_size = get_list_size(*env);
// 	tmp = ft_strdup("");
// 	if (!tmp)
// 		return (NULL);
// 	result = malloc(sizeof(char *) * get_list_size(list_size) + 1);
// 	if (!result)
// 		return (NULL);
// 	while (i < list_size)
// 	{
// 		result[i] = ft_strjoin(tmp, temp->key);
		
		
// 		i++;
// 	}
// 	return (result);
// }
