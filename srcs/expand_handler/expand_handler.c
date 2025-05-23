/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:41:07 by tmarion           #+#    #+#             */
/*   Updated: 2025/05/23 15:42:14 by tmarion          ###   ########.fr       */
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

t_bool	*expand_data_init(t_expand *data, t_env *env, char *token)
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
	return (NULL);
}

char	*expander(t_env *env, char *token)
{
	t_expand	data;

	if (expand_data_init(&data, env, token))
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

t_token	*insert_node(char *value, t_quote_type quote_type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->value = ft_strdup(value);
	new->quote_type = quote_type;
	new->next = NULL;
	return (new);
}

t_token	*build_token_chain(char **split, t_quote_type quote_type)
{
	t_token	*head;
	t_token	*last;
	t_token	*new;
	int		i;

	head = NULL;
	last = NULL;
	i = 0;
	while (split[i])
	{
		new = insert_node(split[i], quote_type);
		if (!head)
			head = new;
		else
			last->next = new;
		last = new;
		i++;
	}
	return (head);
}

void	replace_node_with_chain(t_token **lexicon, t_token *curr, t_token *chain)
{
	t_token	*prev;
	t_token	*temp;
	t_token	*last;

	prev = NULL;
	temp = *lexicon;
	last = chain;
	while (temp && temp != curr)
	{
		prev = temp;
		temp = temp->next;
	}
	if (last)
	{
		while (last->next)
			last = last->next;
	}
	if (prev)
		prev->next = chain;
	else
		*lexicon = chain;
	if (last)
		last->next = curr->next;
	free(curr->value);
	free(curr);
}

void	expand_handler(t_env *env, t_token *lexicon)
{
	t_token	*temp;
	// t_token	*next;
	// t_token	*chain;
	char	*expanded;
	// char	**split;

	temp = lexicon;
	while (temp)
	{
		// next = temp->next;
		if (temp->quote_type != SINGLE)
		{
			expanded = expander(env, temp->value);
			free(temp->value);
			// if (temp->quote_type == NONE)
			// {
			// 	split = ft_split(expanded, ' ');
			// 	chain = build_token_chain(split, NONE);
			// 	replace_node_with_chain(lexicon, temp, chain);
			// 	free_tab(split);
			// }
			// else
				temp->value = expanded;
		}
		temp = temp->next;
	}
}
