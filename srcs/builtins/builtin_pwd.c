/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:42:10 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/01 17:28:23 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

char	*get_pwd_from_env(char **envp)
{
	int	i;
	char *cwd_env;

	i = 0;
	cwd_env = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
		{
			cwd_env = ft_strchr(envp[i], '=');
			if (cwd_env && *(cwd_env + 1))
				cwd_env++;
			break ;
		}
		i++;
	}
	return (cwd_env);
}

void	fetch_cwd(char **envp)
{
	char	*cwd;
	
	cwd = malloc(sizeof(char) * 1024);
	if (!cwd)
	{
		strerror(ENOMEM);
		return ;
	}
	if (!envp || !*envp)
	{	
		if (getcwd(cwd, 1024) == NULL)
		{
			perror("getwcd failed");
			free(cwd);
			return ;
		}
	}
	else
	{
		free(cwd);
		cwd = get_pwd_from_env(envp);
	}
	ft_putendl_fd(cwd, 1);
}
