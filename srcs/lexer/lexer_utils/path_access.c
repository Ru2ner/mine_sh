/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_access.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:34:45 by tmarion           #+#    #+#             */
/*   Updated: 2025/04/23 13:16:54 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

char	**get_paths(char **env)
{
	char	**path;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = ft_split(env[i] + 5, ':');
			if (!path)
				return (NULL);
			return (path);
		}
		i++;
	}
	return (NULL);
}


char	**cmd_arg(char *cmd)
{
	char	**arg;

	if (!cmd)
		return (NULL);
	arg = ft_split(cmd, ' ');
	if (!arg)
		return (NULL);
	return (arg);
}

char	*cmd_path(char *cmd, char **path)
{
	char	*temp;
	char	*tempo;
	int		i;

	i = 0;
	if (!cmd || !path)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
	}
	while (path[i])
	{
		temp = ft_strdup(path[i]);
		temp = ft_strjoin(temp, "/");
		tempo = ft_strjoin(temp, cmd);
		if (!tempo)
			return (NULL);
		if (access(tempo, X_OK) == 0)
			return (tempo);
		i++;
		free(tempo);
	}
	return (NULL);
}
