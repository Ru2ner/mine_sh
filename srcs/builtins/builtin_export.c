/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:42:06 by tlutz             #+#    #+#             */
/*   Updated: 2025/06/05 16:05:39 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

static int	export_helper(t_env *env, char **args)
{
	t_env		*temp;
	t_keyval	key_val;

	temp = env;
	while (temp)
	{
		if (ft_strcmp(temp->key, args[0]) == 0)
			return (edit_var(temp, args));
		temp = temp->next;
	}
	key_value_creator(&key_val, args);
	build_list(&env, &key_val, TRUE, TRUE);
	free(args);
	return (0);
}

int	export(t_env *env, char *arg)
{
	char		**args;

	if (!arg)
		return (print_export(env));
	if (ft_strchr(arg, '=') == NULL)
		return (add_to_export_list(&env, arg));
	if (ft_strnstr(arg, "+=", ft_strlen(arg)))
		return (append_to_var(env, arg));
	args = ft_split(arg, '=');
	if (!args)
		return (malloc_error_int());
	if (!is_valid_for_env_var(args[0]))
	{
		invalid_env_var(args[0]);
		free_tab(args);
		return (1);
	}
	return (export_helper(env, args));
}
