/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:04:29 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/03 19:38:18 by tlutz            ###   ########.fr       */
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
# include <stdbool.h>\

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define BLUE "\033[1;34m"
# define RESET "\033[0m"

typedef struct s_env	t_env;

typedef struct s_env
{
	char	*key;
	char	*value;
	t_env	*next;
}	t_env;

/*****************************Tab Utils****************************************/

size_t	get_tab_size(char **tab);

/*****************************Env Convert**************************************/

void	free_list(t_env *env);

size_t	get_list_size(t_env *env);

t_env	*create_new_node(char *var, char *value);

void	build_list(t_env **env, char *var, char *value);

void	convert_env_to_list(char **envp, t_env **env);

/*****************************Error Handling***********************************/

void	*free_tab(char **tab);

/*******************************Main Exec**************************************/

/********************************Builtins**************************************/

void	print_env(t_env *env);

char	*get_pwd_from_env(t_env *env);

void	fetch_cwd(t_env *env);

void	execute_cd(char *path, t_env *env);

void	exec_clear(void);

void	exec_echo(char **args);

t_env	*exec_unset(t_env *env, const char *key);

void	exec_export(t_env *env, char *arg);

#endif