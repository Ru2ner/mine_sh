/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:31:20 by tmarion           #+#    #+#             */
/*   Updated: 2025/05/03 09:36:29 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft.h"
# include "get_next_line.h"
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	char	**paths;
	char	**cmd;
	char	*cmd_path;
	pid_t	pid;
}		t_pipex;

char		*cmd_path(char *cmd, char **path);
char		**get_paths(char **env);
char		**cmd_arg(char *cmd);
void		ft_init(t_pipex *pipex, char **argv, char **env);
void		close_file(t_pipex *pipex);
void		close_pipe(int *fd);
void		ft_free(t_pipex *pipex);
void		ft_free_bonus(t_pipex *pipex, int trigger);
int			exec_cmd(t_pipex *pipex, char **argv, char **env, int i);
void		error_exit_b(char *errormsg, t_pipex *pipex);
void		perror_exit_b(char *errormsg, t_pipex *pipex);
void		ft_init_bonus(t_pipex *pipex, char **env);
void		open_fd(t_pipex *pipex, char **argv, int argc);
void		second_process(t_pipex *pipex, int *pipe_fd);
int			end_process(t_pipex *pipex, char **argv, char **env, int i);
int			is_here(int argc, char **argv, t_pipex *pipex);

#endif