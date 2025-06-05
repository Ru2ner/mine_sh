/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:45:18 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/29 15:45:56 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

char	*mygetenv(t_env *env, char *var)
{
	char	*result;

	result = NULL;
	if (!env)
		return (NULL);
	while (env)
	{
		if (ft_strcmp(env->key, var) == 0)
		{
			result = ft_strdup(env->value);
			if (!result)
				return (malloc_error());
			return (result);
		}
		env = env->next;
	}
	return (result);
}

void	*update_old_cwd(t_env **env, char *old_wd)
{
	t_env		*curr;

	curr = *env;
	while (curr)
	{
		if (ft_strcmp(curr->key, "OLDPWD") == 0)
		{
			free(curr->value);
			curr->value = old_wd;
			if (!curr->value)
				return (malloc_error());
			if (curr->env == FALSE)
				curr->env = TRUE;
			return (NULL);
		}
		curr = curr->next;
	}
	return (NULL);
}

void	*update_cwd(t_env *env)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (malloc_error());
	while (env)
	{
		if (ft_strcmp(env->key, "PWD") == 0)
		{
			free(env->value);
			env->value = ft_strdup(cwd);
			if (!env->value)
				return (malloc_error());
			break ;
		}
		env = env->next;
	}
	free(cwd);
	return (NULL);
}
