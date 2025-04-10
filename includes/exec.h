/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:04:29 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/10 19:15:57 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include "errors.h"

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define BLUE "\033[1;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define RESET "\033[0m"
# define PROMPT "\033[1;31mminishell> \033[0m"

typedef struct s_env	t_env;
typedef struct s_token	t_token;
typedef struct s_exec	t_exec;

typedef enum e_bool
{
	false,
	true	
}	t_bool;

typedef struct s_env
{
	char	*key;
	char	*value;
	t_bool	export;
	t_bool	env;
	t_env	*next;
}	t_env;

typedef struct s_keyval
{
	char	*key;
	char	*value;
}	t_keyval;

/*****************************Tab Utils****************************************/

size_t	get_tab_size(char **tab);

/*****************************Env Convert**************************************/

void	free_list(t_env *env);

void	*free_dest(char **dest, int j);

size_t	get_list_size(t_env *env);

t_env	*create_new_node(char *var, char *value, t_bool print, t_bool export);

void	build_list(t_env **env, t_keyval *key_val, t_bool print, t_bool export);

void	*convert_env_to_list(char **envp, t_env **env);

char	**convert_env_to_tab(t_env *env);

/*****************************Error Handling***********************************/

void	*free_tab(char **tab);

/*******************************Main Exec**************************************/

/********************************Builtins**************************************/

void	print_env(t_env *env);

char	*get_pwd_from_env(t_env *env);

void	*fetch_cwd(t_env *env);

void	*execute_cd(char *path, t_env *env);

void	exec_clear(void);

void	exec_echo(char **args);

t_env	*exec_unset(t_env *env, const char *key);

void	*exec_export(t_env *env, char *arg);

void	*add_to_export_list(t_env *env, char *arg);

void	*print_export(t_env *env);

#endif