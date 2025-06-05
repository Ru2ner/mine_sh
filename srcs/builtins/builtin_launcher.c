/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_launcher.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:49:07 by tlutz             #+#    #+#             */
/*   Updated: 2025/06/05 12:11:50 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

static int	exec_unset(t_env **env, char **args)
{
	size_t	i;
	int		exit_code;
	int		error;

	i = 1;
	error = 0;
	while (args[i])
	{
		exit_code = unset(env, args[i]);
		if (exit_code == 1)
			error = 1;
		i++;
	}
	return (error);
}

static int	exec_export(t_env *env, char **args)
{
	size_t	i;
	int		exit_code;
	int		error;

	i = 1;
	error = 0;
	if (args[1] == NULL)
		return (export(env, NULL));
	while (args[i])
	{
		exit_code = export(env, args[i]);
		if (exit_code == 1)
			error = 1;
		i++;
	}
	return (error);
}

int	builtin_launcher(t_mshell *mshell, char **args, t_exec *data)
{
	if (args[0] && ft_strcmp(args[0], "env") == 0)
		return (print_env(mshell->env));
	else if (args[0] && ft_strcmp(args[0], "pwd") == 0)
		return (fetch_cwd());
	else if (args[0] && ft_strcmp(args[0], "cd") == 0)
		return (execute_cd(args[1], mshell->env));
	else if (args[0] && ft_strcmp(args[0], "echo") == 0)
		return (exec_echo(args));
	else if (args[0] && ft_strcmp(args[0], "clear") == 0)
		return (exec_clear());
	else if (args[0] && ft_strcmp(args[0], "unset") == 0)
		return (exec_unset(&mshell->env, args));
	else if (args[0] && ft_strcmp(args[0], "export") == 0)
		return (exec_export(mshell->env, args));
	else if (args[0] && ft_strcmp(args[0], "exit") == 0)
		return (exec_exit(mshell, args, data));
	return (0);
}
