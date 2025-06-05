/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:41:28 by tlutz             #+#    #+#             */
/*   Updated: 2025/06/05 13:07:29 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

t_bool	is_arg_number(const char *arg)
{
	if (!arg || !*arg)
		return (FALSE);
	if (*arg == '-' || *arg == '+')
		arg++;
	if (!*arg)
		return (FALSE);
	while (*arg)
	{
		if (*arg < '0' || *arg > '9')
			return (FALSE);
		arg++;
	}
	return (TRUE);
}

void	cleanup_before_exit(t_mshell *sh, char **args, t_exec *data, int option)
{
	if (option == 1)
	{
		free_list(sh->env);
		free_cmd_list(data->cmd_list);
		free_tab(data->envp);
		free(data->tab_pids);
		exit(sh->exit_status);
	}
	if (option == 2)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric arguments required\n", 2);
		free_list(sh->env);
		free_cmd_list(data->cmd_list);
		free_tab(data->envp);
		free(data->tab_pids);
		exit(2);
	}
}

int	exec_exit(t_mshell *sh, char **args, t_exec *data)
{
	int	status;

	if (isatty(0))
		ft_putendl_fd("exit", 2);
	if (!args[1])
		cleanup_before_exit(sh, args, data, 1);
	if (!is_arg_number(args[1]))
		cleanup_before_exit(sh, args, data, 2);
	if (args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		sh->exit_status = 1;
		return (1);
	}
	status = (unsigned char)ft_atoi(args[1]);
	free_list(sh->env);
	free_cmd_list(data->cmd_list);
	free_tab(data->envp);
	free(data->tab_pids);
	exit(status);
}
