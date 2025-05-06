/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:08:09 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/06 20:20:58 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	io_handler(t_cmd *cmd, int in_or_out)
{
	int	fd;

	fd = -2;
	if (in_or_out == 1 && cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd == -1)
		{
			perror(cmd->infile);
			return (fd);
		}
	}
	if (in_or_out == 2 && cmd->outfile)
	{
		if (cmd->append = true)
			fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror(cmd->outfile);
			return (fd);
		}
	}
	return (fd);
}

void	execute_command(t_cmd *cmd)
{
	int		fd_in;
	int		fd_out;
	int		pipe_fd[2];
	pid_t	pid;

	fd_in = io_handler(cmd, 1);
	fd_out = io_handler(cmd, 2);
	if (cmd->pipe)
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe failed :");
			return (NULL);
		}
	pid = fork();
	if (pid == -1)
	{
		perror("forks failed :");
		return ;
	}
	if (pid == 0)
	{
		if (fd_in != -1 && fd_in != -2)
			dup2(fd_in, STDIN_FILENO);
		if (cmd->pipe)
			dup2(pipe_fd[1], STDOUT_FILENO);
		close(fd_in);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
}

void	exec_handler(t_cmd *cmds)
{
	t_cmd	*temp;

	temp = cmds;
	while (cmds)
	{
		execute_command(temp);
		temp = temp->next;
	}
}

