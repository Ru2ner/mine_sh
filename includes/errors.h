/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:57:58 by tlutz             #+#    #+#             */
/*   Updated: 2025/06/05 15:54:44 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# ifndef DEBUG
#  define DEBUG 0
# endif

# include "exec.h"
# include "structs.h"

# define NOSUCHFILEORDIR 0
# define NOPERMS 1
# define NOTADIR 2
# define HOMENOTSET 3
# define HOME_ERR_STR "minishell : cd: HOME not set"

void	*cd_error(int errnum);

void	*malloc_error(void);

void	*cmd_not_found_error(char *str);

int		invalid_env_var(char *arg);

void	add_to_garbage(t_garbage **garbage, void **dptr, \
	void *ptr, t_bool double_p);

void	cleanup_garbage(t_garbage *garbage);

int		malloc_error_int(void);

void	cleanup_minishell(t_mshell *mshell);

void	cleanup_for_child(t_mshell *mshell, t_exec *data, int err, char *arg);

/***************************DEBUG******************************************** */

void	print_lexer(t_token *lexicon);

void	print_exec_list(t_cmd *cmd_list);
#endif