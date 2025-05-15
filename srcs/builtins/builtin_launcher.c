/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_launcher.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:49:07 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/15 15:29:48 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

static t_env	*exec_unset(t_env *env, char **args)
{
	size_t	i;
	
	i = 1;
	while (args[i])
	{
		env = unset(env, args[i]);
		i++;
	}
	return (env);
}

static void	*exec_export(t_env *env, char **args)
{
	size_t	i;
	
	i = 1;
	if (args[1] == NULL)
		export(env, NULL);
	while (args[i])
	{
		export(env, args[i]);
		i++;
	}
	return (NULL);
}

t_env	*builtin_launcher(char **args, t_env *env)
{
	if (args[0] && ft_strcmp(args[0], "env") == 0)
		print_env(env);
	else if (args[0] && ft_strcmp(args[0], "pwd") == 0)
		fetch_cwd(env);
	else if (args[0] && ft_strcmp(args[0], "cd") == 0)
		execute_cd(args[1], env);
	else if (args[0] && ft_strcmp(args[0], "echo") == 0)
		exec_echo(args);
	else if (args[0] && ft_strcmp(args[0], "clear") == 0)
		exec_clear();
	else if (args[0] && ft_strcmp(args[0], "unset") == 0)
		env = exec_unset(env, args);
	else if (args[0] && ft_strcmp(args[0], "export") == 0)
		exec_export(env, args);
	return (env);
}
