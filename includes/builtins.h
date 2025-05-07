/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:02:54 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/07 15:45:19 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "env_handling.h"

/********************************Builtins**************************************/

void	print_env(t_env *env);

char	*get_pwd_from_env(t_env *env);

void	*fetch_cwd(t_env *env);

void	*execute_cd(char *path, t_env *env);

void	exec_clear(void);

void	exec_echo(char **args);

t_env	*unset(t_env *env, const char *key);

void	*export(t_env *env, char *arg);

void	*add_to_export_list(t_env **env, char *arg);

void	*print_export(t_env *env);

t_env	*builtin_launcher(char **args, t_env *env);

#endif