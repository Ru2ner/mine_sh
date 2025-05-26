/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_finder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:54:16 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/26 14:10:19 by tmarion          ###   ########.fr       */
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

char	*find_in_path(char **paths, char *cmd)
{
	char	*complete_path;
	int		i;

	i = 0;
	while (paths && paths[i])
	{
		complete_path = ft_strcjoin(paths[i], cmd, '/');
		if (!complete_path)
			return (malloc_error());
		if (access(complete_path, X_OK) == 0)
			return (complete_path);
		free(complete_path);
		i++;
	}
	return (NULL);
}

char	*parse_path(char **envp, char *cmd)
{
	char	**paths;
	char	*complete_path;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		else
			return (NULL);
	}
	paths = get_path_var(envp);
	complete_path = find_in_path(paths, cmd);
	if (!complete_path)
	{
		free_tab(paths);
		return (NULL);
	}
	free_tab(paths);
	return (complete_path);
}
