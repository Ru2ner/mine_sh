/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:37:40 by tlutz             #+#    #+#             */
/*   Updated: 2025/06/05 20:30:43 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include "parsing.h"
#include "get_next_line.h"
#include "errors.h"
#include "sys/wait.h"

void	free_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*temp;
	t_cmd	*next;

	temp = cmd_list;
	while (temp)
	{
		next = temp->next;
		if (temp->args)
			free_tab(temp->args);
		if (temp->infile)
			free(temp->infile);
		if (temp->outfile)
			free(temp->outfile);
		if (temp->heredoc_delim)
			free(temp->heredoc_delim);
		free(temp);
		temp = next;
	}
}

void	close_unused_fds(int prev_fd, int pipe_read_fd, int pipe_write_fd)
{
	if (prev_fd != -1)
		close(prev_fd);
	if (pipe_read_fd != -1)
		close(pipe_read_fd);
	if (pipe_write_fd != -1)
		close(pipe_write_fd);
}

int	here_doc_handler(t_cmd *cmd)
{
	int		here_doc_pipe[2];
	char	*line;
	size_t	len;

	if (pipe(here_doc_pipe) == -1)
		perror_exit("pipe");
	catch_sig_heredoc();
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			write(1, "\n", 1);
			break ;
		}
		len = ft_strlen(line);
		if (len > 0 && line[len -1] == '\n')
			line[len - 1] = '\0';
		if (ft_strcmp(line, cmd->heredoc_delim) == 0)
		{
			free(line);
			break ;
		}
		write(here_doc_pipe[1], line, ft_strlen(line));
		write(here_doc_pipe[1], "\n", 1);
		free(line);
	}
	close(here_doc_pipe[1]);
	return (here_doc_pipe[0]);
}

void	init_data_struct(t_mshell *mshell, t_exec *data, t_cmd *cmd_list)
{
	t_cmd	*temp;
	int		cmd_count;

	cmd_count = 0;
	temp = cmd_list;
	data->cmd_count = 0;
	data->pid_index = 0;
	data->prev_fd = -1;
	data->envp = mshell->env_tab;
	data->pipe_fd[0] = -1;
	data->pipe_fd[1] = -1;
	data->cmd_list = cmd_list;
	data->sigint_killed = FALSE;
	while (temp)
	{
		cmd_count++;
		temp = temp->next;
	}
	data->tab_pids = malloc(sizeof(pid_t) * cmd_count);
	if (!data->tab_pids)
	{
		malloc_error();
		return ;
	}
	data->cmd_count = cmd_count;
}

void	child_process(t_cmd *cmd, t_exec *data, t_mshell *mshell)
{
	char	*complete_path;
	int		exit_status;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	setup_input_fd(cmd, data->prev_fd);
	setup_output_fd(cmd, data->pipe_fd[1]);
	close_unused_fds(data->prev_fd, data->pipe_fd[0], data->pipe_fd[1]);
	if (cmd->args && is_builtin(cmd->args[0]))
	{
		exit_status = builtin_launcher(mshell, cmd->args, data);
		cleanup_for_child(mshell, data, exit_status, NULL);
	}
	complete_path = parse_path(data->envp, cmd->args[0]);
	if (!complete_path || cmd->args[0][0] == '\0')
		cleanup_for_child(mshell, data, 127, cmd->args[0]);
	execve(complete_path, cmd->args, data->envp);
	if (complete_path)
		free(complete_path);
	perror("minishell: ");
	cleanup_for_child(mshell, data, 1, cmd->args[0]);
}
