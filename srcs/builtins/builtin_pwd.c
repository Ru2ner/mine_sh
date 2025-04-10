/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:42:10 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/10 16:10:36 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

char	*get_pwd_from_env(t_env *env)
{
	char	*cwd_env;
	t_env	*temp;

	cwd_env = NULL;
	temp = env;
	while (temp)
	{
		if (ft_strncmp(temp->key, "PWD", 3) == 0)
		{
			cwd_env = ft_strdup(temp->value);
			if (!cwd_env)
				return (malloc_error());
			break ;
		}
		temp = temp->next;
	}
	return (cwd_env);
}

void	*fetch_cwd(t_env *env)
{
	char	*cwd;

	if (env)
		cwd = get_pwd_from_env(env);
	if (!env || !cwd)
	{
		cwd = malloc(sizeof(char) * 1024);
		if (!cwd)
			return (malloc_error());
		if (getcwd(cwd, 1024) == NULL)
		{
			perror("getcwd failed");
			free(cwd);
			return (NULL);
		}
	}
	ft_putendl_fd(cwd, 1);
	free(cwd);
	return (NULL);
}
