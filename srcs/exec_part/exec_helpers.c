/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:28:25 by tlutz             #+#    #+#             */
/*   Updated: 2025/06/05 20:24:09 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parsing.h"
#include "fcntl.h"
#include "sys/wait.h"
#include "libft.h"

t_bool	is_there_pipe(t_cmd *cmd_list)
{
	t_cmd	*temp;

	temp = cmd_list;
	while (temp)
	{
		if (temp->pipe)
			return (TRUE);
		temp = temp->next;
	}
	return (FALSE);
}

void	parent_builtins_handler(t_cmd *cmd, t_mshell *sh, t_exec *data)
{
	int	stdout_save;

	stdout_save = dup(STDOUT_FILENO);
	setup_output_fd(cmd, -1);
	sh->exit_status = builtin_launcher(sh, cmd->args, data);
	dup2(stdout_save, STDOUT_FILENO);
	close(stdout_save);
}
