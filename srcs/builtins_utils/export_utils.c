/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:13:51 by tlutz             #+#    #+#             */
/*   Updated: 2025/06/05 19:12:16 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

int	add_to_export_list(t_env **env, char *arg)
{
	t_keyval	key_value;
	t_env		*temp;

	temp = *env;
	if (!is_valid_for_env_var(arg))
		return (invalid_env_var(arg));
	while (temp)
	{
		if (ft_strcmp(arg, temp->key) == 0)
			return (0);
		temp = temp->next;
	}
	key_value.key = ft_strdup(arg);
	if (!key_value.key)
		return (malloc_error_int());
	key_value.value = NULL;
	build_list(env, &key_value, FALSE, TRUE);
	return (0);
}

void	*key_value_creator(t_keyval *key_val, char **args)
{
	if (args[0] && args[1])
	{
		key_val->key = args[0];
		key_val->value = args[1];
	}
	if ((args[0] && !args[1]) || (args[0] && args[1][0] == '\"' \
		&& args[1][1] == '\"'))
	{
		key_val->key = args[0];
		key_val->value = ft_strdup("");
		if (key_val->value)
			return (malloc_error());
	}
	return (NULL);
}

static int	append_handler(t_env *temp, char **args)
{
	char	*tmp;

	if (temp->value && args[1])
	{
		tmp = ft_strjoin(temp->value, args[1]);
		if (!temp)
			return (malloc_error_int());
	}
	else if (args[1])
	{
		tmp = ft_strdup(args[1]);
		if (!tmp)
			return (malloc_error_int());
	}
	tmp = ft_strdup("");
	if (!tmp)
		return (malloc_error_int());
	free(temp->value);
	temp->value = tmp;
	free_tab(args);
	temp->env = TRUE;
	return (0);
}

int	append_to_var(t_env *env, char *arg)
{
	char		**args;
	t_env		*temp;
	t_keyval	key_val;

	temp = env;
	args = ft_split_charset(arg, "+=");
	if (!is_valid_for_env_var(args[0]))
		return (invalid_env_var(args[0]));
	if (!args)
		return (malloc_error_int());
	while (temp)
	{
		if (ft_strcmp(temp->key, args[0]) == 0)
			return (append_handler(temp, args));
		temp = temp->next;
	}
	key_value_creator(&key_val, args);
	build_list(&env, &key_val, TRUE, TRUE);
	free(args);
	return (0);
}

int	edit_var(t_env *temp, char **args)
{
	free(temp->value);
	if (!args[1])
		temp->value = ft_strdup("");
	else
		temp->value = ft_strdup(args[1]);
	if (!temp->value)
		return (malloc_error_int());
	if (temp->env == FALSE)
		temp->env = TRUE;
	free_tab(args);
	return (0);
}
