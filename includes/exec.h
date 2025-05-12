/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:04:29 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/12 15:45:32 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>

# include "parsing.h"
# include "share_header.h"
# include <structs.h>
# include <errors.h>
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

typedef struct s_env	t_env;
typedef struct s_token	t_token;
typedef struct s_exec	t_exec;


# include "errors.h"

typedef struct s_cmd  t_cmd;

typedef struct s_cmd
{
	char	**args; // Cmd dans le slot 0 et arguments ensuite
	char	*infile; // Ou fd si on peut open plus tôt dans le programme
	char	*outfile; // idem
	t_bool	append; // true pour >> false pour >
	t_bool	pipe; // si pipe ensuite
	char	*heredoc; // Delimiter pour le here_doc, si besoin
	t_cmd	*next;
}	t_cmd;

// typedef struct s_env
// {
// 	char	*key;
// 	char	*value;
// 	t_bool	export;
// 	t_bool	env;
// 	t_env	*next;
// }	t_env;

typedef struct s_keyval
{
	char	*key;
	char	*value;
}	t_keyval;

// typedef struct t_mshell
// {
// 	t_env	*env;
// 	char	**args;
// 	// t_token	*lexicon; --> t_cmd
// }	t_mshell;

/*****************************Tab Utils****************************************/

size_t	get_tab_size(char **tab);

/*****************************Error Handling***********************************/

/*******************************Main Exec**************************************/

void	sigint_handler(int signum);

void	catch_sig(void);

void	perror_exit(const char *msg);

void	close_unused_fds(int prev_fd, int pipe_read_fd, int pipe_write_fd);

int		here_doc_handler(t_cmd *cmd);

char	*expand_handler(t_env *env, char *key);

#endif