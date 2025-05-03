/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:28:14 by tmarion           #+#    #+#             */
/*   Updated: 2025/05/03 09:35:48 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <fcntl.h>
#include <stdlib.h>

static int	read_stdin(char **argv, int *pipe_fd)
{
	char	*temp;
	size_t	i;

	temp = NULL;
	while (1)
	{
		i = ft_strlen(argv[2]);
		temp = get_next_line(0);
		if (!temp)
			return (0);
		if (ft_strncmp(temp, argv[2], i) == 0 && ft_strlen(temp) == i + 1)
		{
			if (pipe_fd[1] != -1)
				close(pipe_fd[1]);
			return (free(temp), 1);  
		}
		ft_putstr_fd(temp, pipe_fd[1]);
		free(temp);
	}
	return (0);
}

void	here_doc(t_pipex *pipex, char **argv)
{
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		perror_exit_b("error; failed to create a pipe", pipex);
	read_stdin(argv, pipe_fd);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		perror_exit_b("error: dup2 failed to STDIN", pipex);
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
}

void	process(t_pipex *pipex, char **argv, char **env, int i)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		perror_exit_b("error; failed to create a pipe", pipex);
	pipex->pid = fork();
	if (pipex->pid == -1)
		perror_exit_b("error: failed to create a fork", pipex);
	if (pipex->pid == 0)
	{
		if (pipe_fd[0] != -1)
			close(pipe_fd[0]);
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			perror_exit_b("error: dup2 failed to STDOUT", pipex);
		close(pipe_fd[1]);
		close_file(pipex);
		exec_cmd(pipex, argv, env, i);
	}
	else
		second_process(pipex, pipe_fd);
	if (pipex->infile != -1)
		close(pipex->infile);
}

void	multiple_pipex(t_pipex *pipex, int argc, char **argv, char **env)
{
	int		i;

	if (ft_strncmp(argv[1], "here_doc", 8) == 0 && ft_strlen(argv[1]) == 8)
	{
		i = 3;
		pipex->outfile = is_here(argc, argv, pipex);
		if (pipex->outfile == -1)
			perror_exit_b("error: failed to open outputfile", pipex);
		here_doc(pipex, argv);
	}
	else
	{
		i = 2;
		open_fd(pipex, argv, argc);
		if (dup2(pipex->infile, STDIN_FILENO) == -1)
			perror_exit_b("error: dup2 failed to STDIN", pipex);
	}
	while (i < argc - 2)
		process(pipex, argv, env, i++);
	end_process(pipex, argv, env, i);
}

// int	main(int argc, char **argv, char **env)
// {
// 	t_pipex	pipex;
// 	int		process;
// 	int		i;

// 	i = 0;
// 	if (argc < 5)
// 	{
// 		ft_putstr_fd("error: Insufficient number of arguments", 2);
// 		return (0);
// 	}
// 	if (ft_strncmp(argv[1], "here_doc", 8) == 0 && ft_strlen(argv[1]) == 8)
// 		i = 1;
// 	ft_init_bonus(&pipex, env);
// 	multiple_pipex(&pipex, argc, argv, env);
// 	ft_free_bonus(&pipex, 1);
// 	while (i < argc - 4)
// 	{
// 		waitpid(-1, &process, 0);
// 		i++;
// 	}
// 	waitpid(pipex.pid, &process, 0);
// 	return (process);
// }
