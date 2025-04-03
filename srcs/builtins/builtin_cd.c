/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:12:53 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/03 18:21:36 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

static void	update_old_cwd(t_env *env, char *old_wd)
{
	while (env)
	{
		if (ft_strcmp(env->key, "OLDPWD") == 0)
		{
			free(env->value);
			env->value = ft_strdup(old_wd);
			if (!env->value)
			{
				strerror(ENOMEM);
				return ;
			}
			break ;
		}
		env = env->next;
	}
	free(old_wd);
}

static void	update_cwd(t_env *env)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		strerror(ENOMEM);
		return ;
	}
	while (env)
	{
		if (ft_strcmp(env->key, "PWD") == 0)
		{
			free(env->value);
			env->value = ft_strdup(cwd);
			if (!env->value)
			{
				strerror(ENOMEM);
				return ;
			}
			break ;
		}
		env = env->next;
	}
	free(cwd);
}

void	execute_cd(char *path, t_env *env)
{
	char	*old_wd;

	old_wd = getcwd(NULL, 0);
	if (!old_wd)
	{
		strerror(ENOMEM);
		return ;
	}
	if (path == NULL || ft_strcmp(path, "~") == 0)
		path = getenv("HOME");
	else if (ft_strcmp(path, "-") == 0)
		path = getenv("OLDPWD");
	if (chdir(path) != 0)
		perror("cd");
	update_old_cwd(env, old_wd);
	update_cwd(env);
}
