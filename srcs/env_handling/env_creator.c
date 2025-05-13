/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:41:07 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/13 13:59:14 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

static void	change_shlvl(t_env *env)
{
	t_env	*temp;
	int		shlvl;

	temp = env;
	while (temp)
	{
		if (ft_strcmp(temp->key, "SHLVL") == 0)
		{
			shlvl = ft_atoi(temp->value);
			shlvl++;
			temp->value = ft_itoa(shlvl);
			break;
		}
		temp = temp->next;
	}
}

static void	create_default_env(t_env **env)
{
	t_keyval	keyval_pwd;
	t_keyval	keyval_path;
	t_keyval	keyval_oldpwd;
	t_keyval	keyval_shlvl;

	keyval_pwd.key = ft_strdup("PWD");
	keyval_pwd.value = getcwd(NULL, 0);
	build_list(env, &keyval_pwd, TRUE, TRUE);
	keyval_path.key = ft_strdup("PATH");
	keyval_path.value = ft_strdup(DEFPATH);
	build_list(env, &keyval_path, TRUE, TRUE);
	keyval_oldpwd.key = ft_strdup("OLDPWD");
	keyval_oldpwd.value = NULL;
	build_list(env, &keyval_oldpwd, FALSE, TRUE);
	keyval_shlvl.key = ft_strdup("SHLVL");
	keyval_shlvl.value = ft_strdup("1");
	build_list(env, &keyval_shlvl, TRUE, TRUE);
}

void	env_creator(char **envp, t_mshell *mshell)
{
	if (envp && *envp)
	{
		convert_env_to_list(envp, &mshell->env);
		change_shlvl(mshell->env);
	}
	else
		create_default_env(&mshell->env);
}
