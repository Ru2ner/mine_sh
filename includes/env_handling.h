/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handling.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:02:51 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/29 19:19:22 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_HANDLING_H
# define ENV_HANDLING_H

# include "structs.h"

/*****************************Env Convert**************************************/

void	free_list(t_env *env);

void	*free_dest(char **dest, int j);

size_t	get_list_size(t_env *env);

t_env	*create_new_node(char *var, char *value, t_bool print, t_bool export);

void	build_list(t_env **env, t_keyval *key_val, t_bool print, t_bool export);

void	*convert_env_to_list(char **envp, t_env **env);

char	**convert_env_to_tab(t_env *env);

void	env_creator(char **envp, t_mshell *mshell);

#endif