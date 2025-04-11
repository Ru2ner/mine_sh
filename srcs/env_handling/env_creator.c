/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:41:07 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/11 19:07:25 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

static void	create_default_env(t_env **env)
{
	t_keyval	keyval_pwd;
	t_keyval	keyval_path;
	t_keyval	keyval_oldpwd;
	char		*cwd;

	cwd = getcwd(NULL, 0);
	keyval_pwd.key = ft_strdup("PWD");
	keyval_pwd.value = cwd;
	build_list(env, &keyval_pwd, true, true);
	keyval_path.key = ft_strdup("PATH");
	keyval_path.value = ft_strdup(DEFPATH);
	build_list(env, &keyval_path, true, true);
	keyval_oldpwd.key = ft_strdup("OLDPWD");
	keyval_oldpwd.value = NULL;
	build_list(env, &keyval_oldpwd, false, true);
}

void	env_creator(char **envp, t_mshell *mshell)
{
	if (envp && *envp)
		convert_env_to_list(envp, &mshell->env);
	else
		create_default_env(&mshell->env);
}
