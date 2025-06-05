/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:12:53 by tlutz             #+#    #+#             */
/*   Updated: 2025/06/04 19:42:44 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

static int	handle_home_cd(t_env *env, char *old_wd)
{
	char	*shortcut_path;

	shortcut_path = mygetenv(env, "HOME");
	if (!shortcut_path)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		return (1);
	}
	if (chdir(shortcut_path) != 0)
	{
		perror("minishell: cd :");
		return (1);
	}
	update_old_cwd(&env, old_wd);
	update_cwd(env);
	if (shortcut_path)
		free(shortcut_path);
	return (0);
}

static int	handle_old_pwd(t_env *env, char *old_wd)
{
	char	*shortcut_path;

	shortcut_path = mygetenv(env, "OLDPWD");
	if (!shortcut_path)
	{
		ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
		return (1);
	}
	if (chdir(shortcut_path) != 0)
	{
		perror("minishell: cd: ");
		return (1);
	}
	update_old_cwd(&env, old_wd);
	update_cwd(env);
	return (0);
}

int	execute_cd(char *path, t_env *env)
{
	char	*old_wd;

	old_wd = getcwd(NULL, 0);
	if (!old_wd)
	{
		malloc_error();
		return (1);
	}
	if (path == NULL || ft_strcmp(path, "~") == 0)
		return (handle_home_cd(env, old_wd));
	else if (ft_strcmp(path, "-") == 0)
		return (handle_old_pwd(env, old_wd));
	if (chdir(path) != 0)
	{
		perror("minishell: cd: ");
		free(old_wd);
		return (1);
	}
	update_old_cwd(&env, old_wd);
	update_cwd(env);
	return (0);
}
