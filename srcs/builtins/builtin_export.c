/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:42:06 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/07 13:30:03 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

static void	*key_value_creator(t_keyval *key_val, char **args)
{
	if (args[0] && args[1])
	{
		key_val->key = args[0];
		key_val->value = args[1];
	}
	if (args[0] && !args[1])
	{
		key_val->key = args[0];
		key_val->value = ft_strdup("");
		if (key_val->value)
			return (malloc_error());
	}
	return (NULL);
}

static void	*append_handler(t_env *temp, char **args)
{
	char	*tmp;

	if (temp->value)
		tmp = ft_strjoin(temp->value, args[1]);
	else
		tmp = ft_strdup(args[1]);
	if (!tmp)
		return (malloc_error());
	free(temp->value);
	temp->value = tmp;
	free_tab(args);
	temp->env = TRUE;
	return (NULL);
}

static void	*append_to_var(t_env *env, char *arg)
{
	char		**args;
	t_env		*temp;
	t_keyval	key_val;

	temp = env;
	args = ft_split_charset(arg, "+=");
	if (!args)
		return (malloc_error());
	while (temp)
	{
		if (ft_strcmp(temp->key, args[0]) == 0)
			return (append_handler(temp, args));
		temp = temp->next;
	}
	key_value_creator(&key_val, args);
	build_list(&env, &key_val, TRUE, TRUE);
	free(args);
	return (NULL);
}

static void	*edit_var(t_env *temp, char **args)
{
	free(temp->value);
	if (!args[1])
		temp->value = ft_strdup("");
	else
		temp->value = ft_strdup(args[1]);
	if (!temp->value)
		return (malloc_error());
	if (temp->env == FALSE)
		temp->env = TRUE;
	free_tab(args);
	return (NULL);
}

void	*export(t_env *env, char *arg)
{
	t_env		*temp;
	char		**args;
	t_keyval	key_val;

	if (!arg)
		return (print_export(env));
	temp = env;
	if (ft_strchr(arg, '=') == NULL)
		return (add_to_export_list(&env, arg));
	if (ft_strnstr(arg, "+=", ft_strlen(arg)))
		return (append_to_var(env, arg));
	args = ft_split(arg, '=');
	if (!args)
		return (malloc_error());
	while (temp)
	{
		if (ft_strcmp(temp->key, args[0]) == 0)
			return (edit_var(temp, args));
		temp = temp->next;
	}
	key_value_creator(&key_val, args);
	build_list(&env, &key_val, TRUE, TRUE);
	free(args);
	return (NULL);
}
