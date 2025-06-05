/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_waiting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:42:09 by tlutz             #+#    #+#             */
/*   Updated: 2025/06/05 20:51:34 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parsing.h"
#include "sys/wait.h"

int	status_checker(int status)
{
	int	last_status;

	if (WIFEXITED(status))
		last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGPIPE)
		last_status = 1;
	else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
	{
		last_status = 128 + WTERMSIG(status);
		ft_putendl_fd("Quit (core dumped)", 2);
	}
	else if (WIFSIGNALED(status))
		last_status = 128 + WTERMSIG(status);
	else
		last_status = status;
	return (last_status);
}

int	child_waiter(t_exec *data)
{
	int	status;
	int	last_status;
	int	i;

	i = 0;
	last_status = 0;
	while (i < data->cmd_count)
	{
		waitpid(data->tab_pids[i], &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			data->sigint_killed = TRUE;
		if (i == data->cmd_count - 1)
			last_status = status_checker(status);
		i++;
	}
	return (last_status);
}
