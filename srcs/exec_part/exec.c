/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:08:09 by tlutz             #+#    #+#             */
/*   Updated: 2025/06/05 20:24:04 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parsing.h"
#include "fcntl.h"
#include "sys/wait.h"
#include "libft.h"

void	setup_input_fd(t_cmd *cmd, int prev_fd)
{
	int	in_fd;
	int	here_doc_fd;

	if (cmd->heredoc_delim)
	{
		here_doc_fd = here_doc_handler(cmd);
		if (dup2(here_doc_fd, STDIN_FILENO) == -1)
			perror_exit("dup2 here_doc_fd");
		close(here_doc_fd);
	}
	else if (cmd->infile)
	{
		in_fd = open(cmd->infile, O_RDONLY);
		if (in_fd == -1)
			perror_exit(cmd->infile);
		if (dup2(in_fd, STDIN_FILENO) == -1)
			perror_exit("dup2 infile");
		close(in_fd);
	}
	else if (prev_fd != -1)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
			perror_exit("dup2 prev_fd");
	}
}

void	setup_output_fd(t_cmd *cmd, int pipe_write_fd)
{
	int	out_fd;

	if (cmd->pipe)
	{
		if (dup2(pipe_write_fd, STDOUT_FILENO) == -1)
			perror_exit("dup2 pipe write");
	}
	else if (cmd->outfile)
	{
		if (cmd->append)
			out_fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			out_fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (out_fd == -1)
			perror_exit(cmd->outfile);
		if (dup2(out_fd, STDOUT_FILENO) == -1)
			perror_exit("dup2 outfile");
		close(out_fd);
	}
}

void	execute_command(t_cmd *cmd, t_exec *data, t_mshell *mshell)
{
	pid_t	pid;

	if (cmd->pipe)
	{
		if (pipe(data->pipe_fd) == -1)
			perror_exit("pipe");
	}
	else
	{
		data->pipe_fd[0] = -1;
		data->pipe_fd[1] = -1;
	}
	pid = fork();
	if (pid == 0)
		child_process(cmd, data, mshell);
	else
	{
		if (data->prev_fd != -1)
			close(data->prev_fd);
		if (data->pipe_fd[1] != -1)
			close(data->pipe_fd[1]);
		data->tab_pids[data->pid_index++] = pid;
	}
}

void	pipeline_loop(t_cmd *cmd, t_mshell *sh, t_exec *data, t_bool *forked)
{
	t_bool	piped;

	piped = is_there_pipe(cmd);
	while (cmd)
	{
		if (cmd->args && is_builtin(cmd->args[0]) && !piped)
			parent_builtins_handler(cmd, sh, data);
		else
		{
			execute_command(cmd, data, sh);
			*forked = TRUE;
		}
		if (data->prev_fd != -1)
			close(data->prev_fd);
		if (cmd->pipe)
			data->prev_fd = data->pipe_fd[0];
		else
			data->prev_fd = -1;
		cmd = cmd->next;
	}
}

void	pipeline(t_cmd *cmd_list, t_mshell *mshell)
{
	t_cmd	*cmd;
	t_exec	data;
	t_bool	forked;

	cmd = cmd_list;
	forked = FALSE;
	init_data_struct(mshell, &data, cmd_list);
	pipeline_loop(cmd, mshell, &data, &forked);
	signal(SIGINT, SIG_IGN);
	if (forked)
		mshell->exit_status = child_waiter(&data);
	free(data.tab_pids);
	catch_sig();
	if (data.sigint_killed)
		write(1, "\n", 1);
}
