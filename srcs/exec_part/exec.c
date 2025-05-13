/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:08:09 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/13 14:49:21 by tlutz            ###   ########.fr       */
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

void	child_process(t_cmd *cmd, int prev_fd, int *pipe_fd, char **envp)
{
	char	*complete_path;
	
	setup_input_fd(cmd, prev_fd);
	setup_output_fd(cmd, pipe_fd[1]);
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	if (prev_fd != -1)
		close(prev_fd);
	complete_path = parse_path(envp, cmd->args[0]);
	execve(complete_path, cmd->args, envp);
	perror_exit("execve");
}

void	execute_command(t_cmd *cmd, int prev_fd, int *pipe_fd, char **envp)
{
	pid_t	pid;

	if (cmd->pipe)
	{
		if (pipe(pipe_fd) == -1)
			perror_exit("pipe");
	}
	else
	{
		pipe_fd[0] = -1;
		pipe_fd[1] = -1;
	}
	pid = fork();
	if (pid == 0)
		child_process(cmd, prev_fd, pipe_fd, envp);
	else
	{
		if (prev_fd != -1)
			close(prev_fd);
		if (pipe_fd[1] != -1)
			close(pipe_fd[1]);
	}
}

void	pipeline(t_cmd *cmd_list, char **envp, t_mshell *mshell)
{
	int		prev_fd;
	int		pipe_fd[2];
	t_cmd	*cmd;
	int		status;
	(void)mshell;

	prev_fd = -1;
	cmd = cmd_list;
	while (cmd)
	{
		if (cmd->args && is_builtin(cmd->args[0]))
			mshell->env = builtin_launcher(mshell->args, mshell->env);
		else
			execute_command(cmd, prev_fd, pipe_fd, envp);
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->pipe)
			prev_fd = pipe_fd[0];
		else
			prev_fd = -1;
		cmd = cmd->next;
	}
	while (wait(&status) > 0)
		;
}
