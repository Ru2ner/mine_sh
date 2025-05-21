/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:41:07 by tmarion           #+#    #+#             */
/*   Updated: 2025/05/21 18:13:30 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

char	*extract_var_name(char *str, size_t *var_len)
{
	size_t	i;
	size_t	j;
	char	*dest;

	i = 0;
	j = 0;
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
	{
		*var_len = 0;
		return (NULL);
	}
	while ((ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	dest = malloc(i + 1);
	if (!dest)
		return (malloc_error());
	while (j < i)
	{
		dest[j] = str[j];
		j++;
	}
	dest[i] = '\0';
	*var_len = i;
	return (dest);
}

size_t	compute_expanded_length(t_env *env, char *token)
{
	size_t	len;
	size_t	i;
	size_t	var_len;
	char	*var_value;
	char	*var_name;

	i = 0;
	len = 0;
	while (token[i])
	{
		if (token[i] == '$' && (ft_isalpha(token[i + 1]) || token[i + 1] == '_'))
		{
			var_name = extract_var_name(token + i + 1, &var_len);
			if (var_len > 0 && var_name)
			{
				var_value = fetch_value_from_env(env, var_name);
				if (!var_value)
					var_value = "";
				len += ft_strlen(var_value);
				free(var_name);
				i += 1 + var_len;
				continue ;
			}
			free(var_name);
		}
		len++;
		i++;
	}
	return (len);
}

void	*expand_data_init(t_expand *data, t_env *env, char *token)
{
	data->i = 0;
	data->out_i = 0;
	data->var_len = 0;
	data->var_name = NULL;
	data->var_value = NULL;
	data->expanded_len = compute_expanded_length(env, token);
	data->expanded = malloc(data->expanded_len + 1);
	if (!data->expanded)
		return (malloc_error());
}

char	*expand_handler(t_env *env, char *token)
{
	t_expand	data;

	if (expand_data_init(&data, env, token));
		return (NULL);
	while (token[data.i])
	{	
		if (token[data.i] == '$' && (ft_isalpha(token [data.i + 1]) || token[data.i + 1] == '_'))
		{
			data.var_name = extract_var_name(token + data.i + 1, &data.var_len);
			if (data.var_len > 0 && data.var_name)
			{
				data.var_value = fetch_value_from_env(env, data.var_name);
				if (!data.var_value)
					data.var_value  = "";
				data.val_len = ft_strlen(data.var_value);
				ft_memcpy(data.expanded + data.out_i, data.var_value, data.val_len);
				data.out_i += data.val_len;
				data.i += 1 + data.var_len;
				free(data.var_name);
				continue ;
			}
			free(data.var_name);
		}
		data.expanded[data.out_i++] = token[data.i++];
	}
	data.expanded[data.out_i] = '\0';
	return (data.expanded);
}
