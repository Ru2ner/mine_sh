/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:43:05 by tlutz             #+#    #+#             */
/*   Updated: 2025/06/05 18:23:44 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	cleanup_minishell(t_mshell *mshell)
{
	free_list(mshell->env);
	cleanup_garbage(mshell->g_collector);
}

void	cleanup_for_child(t_mshell *mshell, t_exec *data, int err, char *arg)
{
	if (err == 127)
	{
		cmd_not_found_error(arg);
		free_list(mshell->env);
		free_cmd_list(data->cmd_list);
		free_tab(data->envp);
		free(data->tab_pids);
		exit(127);
	}
	else
	{
		free_list(mshell->env);
		free_cmd_list(data->cmd_list);
		free_tab(data->envp);
		free(data->tab_pids);
		exit(err);
	}
}
