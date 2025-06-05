/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:02:54 by tlutz             #+#    #+#             */
/*   Updated: 2025/06/05 12:16:45 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "env_handling.h"

/********************************Builtins**************************************/

int		print_env(t_env *env);

char	*mygetenv(t_env *env, char *var);

void	*update_old_cwd(t_env **env, char *old_wd);

void	*update_cwd(t_env *env);

int		fetch_cwd(void);

int		execute_cd(char *path, t_env *env);

int		exec_clear(void);

int		exec_echo(char **args);

int		unset(t_env **env, const char *key);

int		export(t_env *env, char *arg);

int		add_to_export_list(t_env **env, char *arg);

int		append_to_var(t_env *env, char *arg);

int		edit_var(t_env *temp, char **args);

void	*key_value_creator(t_keyval *key_val, char **args);

int		print_export(t_env *env);

int		builtin_launcher(t_mshell *mshell, char **args, t_exec *data);

int		exec_exit(t_mshell *sh, char **args, t_exec *data);

#endif