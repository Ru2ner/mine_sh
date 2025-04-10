/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:12:53 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/10 16:11:53 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

static char	*mygetenv(t_env *env, char *var)
{
	char	*result;

	result = NULL;
	if (!env)
		return (NULL);
	while (env)
	{
		if (ft_strcmp(env->key, var) == 0)
		{
			result = ft_strdup(env->value);
			if (!result)
				return (malloc_error());
			return (result);
		}
		env = env->next;
	}
	return (result);
}

static void	*update_old_cwd(t_env *env, char *old_wd)
{
	while (env)
	{
		if (ft_strcmp(env->key, "OLDPWD") == 0)
		{
			free(env->value);
			env->value = ft_strdup(old_wd);
			if (!env->value)
				return (malloc_error());
			break ;
		}
		env = env->next;
	}
	free(old_wd);
	return (NULL);
}

static void	*update_cwd(t_env *env)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		strerror(ENOMEM);
		return (NULL);
	}
	while (env)
	{
		if (ft_strcmp(env->key, "PWD") == 0)
		{
			free(env->value);
			env->value = ft_strdup(cwd);
			if (!env->value)
				return (malloc_error());
			break ;
		}
		env = env->next;
	}
	free(cwd);
	return (NULL);
}

void	*execute_cd(char *path, t_env *env)
{
	char	*old_wd;
	char	*shortcut_path;

	old_wd = getcwd(NULL, 0);
	shortcut_path = NULL;
	if (!old_wd)
		return (malloc_error());
	if (path == NULL || ft_strcmp(path, "~") == 0)
		shortcut_path = mygetenv(env, "HOME");
	else if (ft_strcmp(path, "-") == 0)
		shortcut_path = mygetenv(env, "OLDPWD");
	if (shortcut_path)
	{
		if (chdir(shortcut_path) != 0)
			perror("cd");
	}
	else if (path)
		if (chdir(path) != 0)
			perror("cd");
	update_old_cwd(env, old_wd);
	update_cwd(env);
	if (shortcut_path)
		free(shortcut_path);
	return (NULL);
}
