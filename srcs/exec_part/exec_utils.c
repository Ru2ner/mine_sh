/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:37:40 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/15 15:53:09 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include "get_next_line.h"

void	perror_exit(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
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
			break;
		}
		len = ft_strlen(line);
		if (len > 0 && line[len -1] == '\n')
			line[len - 1] = '\0';
		if (ft_strcmp(line, cmd->heredoc_delim) == 0)
		{
			free(line);
			break;
		}
		write(here_doc_pipe[1], line, ft_strlen(line));
		write(here_doc_pipe[1], "\n", 1);
		free(line);
	}
	close(here_doc_pipe[1]);
	return (here_doc_pipe[0]);
}
