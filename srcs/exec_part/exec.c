/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:08:09 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/20 12:49:35 by tlutz            ###   ########.fr       */
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

void	child_process(t_cmd *cmd, t_exec *data, t_env *env)
{
	char	*complete_path;
	
	signal(SIGINT, SIG_DFL);
	setup_input_fd(cmd, data->prev_fd);
	setup_output_fd(cmd, data->pipe_fd[1]);
	if (data->pipe_fd[0] != -1)
		close(data->pipe_fd[0]);
	if (data->pipe_fd[1] != -1)
		close(data->pipe_fd[1]);
	if (data->prev_fd != -1)
		close(data->prev_fd);
	if (cmd->args && is_builtin(cmd->args[0]))
	{
		builtin_launcher(cmd->args, &env);
		free_list(env);
		free_lexicon(data->lexicon);
		free_cmd_list(data->cmd_list);
		exit(1);
	}
	complete_path = parse_path(data->envp, cmd->args[0]);
	// printf("%s\n", complete_path);
	if (!complete_path)
	{
		cmd_not_found_error();
		exit(127);
	}
	execve(complete_path, cmd->args, data->envp);
	perror_exit("execve");
}

void	execute_command(t_cmd *cmd, t_exec *data, t_env *env)
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
		child_process(cmd, data, env);
	else
	{
		if (data->prev_fd != -1)
			close(data->prev_fd);
		if (data->pipe_fd[1] != -1)
			close(data->pipe_fd[1]);
	}
}

void	pipeline(t_cmd *cmd_list, char **envp, t_mshell *mshell, t_token *lexicon)
{
	t_cmd	*cmd;
	t_bool	sigint_killed;
	t_exec	data;

	data.prev_fd = -1;
	cmd = cmd_list;
	sigint_killed = FALSE;
	data.envp = envp;
	data.pipe_fd[0] = -1;
	data.pipe_fd[1] = -1;
	data.cmd_list = cmd_list;
	data.lexicon = lexicon;
	while (cmd)
	{
		if (cmd->args && is_builtin(cmd->args[0]) && !cmd->pipe)
			builtin_launcher(cmd->args, &mshell->env);
		else
			execute_command(cmd, &data, mshell->env);
		if (data.prev_fd != -1)
			close(data.prev_fd);
		if (cmd->pipe)
			data.prev_fd = data.pipe_fd[0];
		else
			data.prev_fd = -1;
		cmd = cmd->next;
	}
	signal(SIGINT, SIG_IGN);
	while (wait(&data.status) > 0)
	{
		if (WIFSIGNALED(data.status) && WTERMSIG(data.status) == SIGINT)
			sigint_killed = TRUE;
	}
	catch_sig();
	if (sigint_killed)
		write(1, "\n", 1);
}
