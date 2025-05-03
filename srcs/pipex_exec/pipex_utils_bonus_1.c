/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:21:14 by tmarion           #+#    #+#             */
/*   Updated: 2025/05/03 09:31:24 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	second_process(t_pipex *pipex, int *pipe_fd)
{
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		perror_exit_b("error: dup2 failed to STDIN", pipex);
	if (pipex->infile != -1)
		close(pipex->infile);
	close_pipe(pipe_fd);
}

static void	second_free(t_pipex *pipex)
{
	if (pipex->paths)
		free(pipex->paths);
	if (pipex->cmd_path)
		free(pipex->cmd_path);
}

void	ft_free(t_pipex *pipex)
{
	int	i;

	i = -1;
	if (!pipex)
		return ;
	if (pipex->cmd)
	{
		while (pipex->cmd[++i])
			free(pipex->cmd[i]);
		free(pipex->cmd);
	}
	i = -1;
	while (pipex->paths && pipex->paths[++i])
		free(pipex->paths[i]);
	second_free(pipex);
}

