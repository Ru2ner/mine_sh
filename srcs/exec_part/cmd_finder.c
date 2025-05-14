/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_finder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:54:16 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/14 20:58:14 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "libft.h"

static char	**get_path_var(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	if (!envp[0])
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			if (!paths)
				return (malloc_error());
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*parse_path(char **envp, char *cmd)
{
	char	*complete_path;
	char	**paths;
	int		i;

	i = 0;
	if (ft_strchr(cmd, '/'))
		if (access(cmd, X_OK) == 0)
			return (cmd);
	paths = get_path_var(envp);
	while (paths && paths[i])
	{
		complete_path = ft_strcjoin(paths[i], cmd, '/');
		if (!complete_path)
			return (malloc_error());
		if (access(complete_path, X_OK) == 0)
		{
			free_tab(paths);
			return (complete_path);
		}
		free(complete_path);
		i++;
	}
	free_tab(paths);
	return (NULL);
}
