/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:04:29 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/20 14:38:51 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>

# include "structs.h"
# include "errors.h"
# include "env_handling.h"
# include "builtins.h"

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define BLUE "\033[1;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define RESET "\033[0m"
# define PROMPT "\033[1;31mminishell> \033[0m"
# define DEFPATH "/usr/bin"

/*****************************Tab Utils****************************************/

size_t	get_tab_size(char **tab);

void	free_tab(char **tab);

/*******************************Main Exec**************************************/

void	sigint_handler(int signum);

void	catch_sig(void);

void	perror_exit(const char *msg);

void	close_unused_fds(int prev_fd, int pipe_read_fd, int pipe_write_fd);

int		here_doc_handler(t_cmd *cmd);

char	*expand_handler(t_env *env, char *key);

int 	exec(t_token *lexicon, char **envp, t_mshell *mshell);

char	*parse_path(char **envp, char *cmd);

void	pipeline(t_cmd *cmd_list, char **envp, t_mshell *mshell, t_token *lexicon);

void	catch_sig_heredoc(void);

char	*fetch_value_from_env(t_env *env, char *key);

char	*create_prompt(t_env *env);

void	free_cmd_list(t_cmd *cmd_list);

#endif