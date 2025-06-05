/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:41:07 by tmarion           #+#    #+#             */
/*   Updated: 2025/06/05 20:27:02 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include "parsing.h"

char	*extract_var_name(char *str, size_t *var_len)
{
	size_t	i;
	size_t	j;
	char	*dest;

	i = 0;
	j = 0;
	if (str[0] == '?')
	{
		dest = malloc(2);
		if (!dest)
			return (malloc_error());
		dest[0] = '?';
		dest[1] = '\0';
		*var_len = 1;
		return (dest);
	}
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

size_t	compute_expanded_length(t_mshell *mshell, t_env *env, char *token)
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
		if (token[i] == '$' && token[i + 1] && (ft_isalpha(token[i + 1]) || token[i + 1] == '_' || token[i + 1] == '?'))
		{
			var_name = extract_var_name(token + i + 1, &var_len);
			if (var_len > 0 && var_name)
			{
				var_value = fetch_value_from_env(mshell, env, var_name);
				if (!var_value)
					var_value = "";
				len += ft_strlen(var_value);
				if (ft_strcmp(var_name, "?") == 0)
					free(var_value);
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

char	*expander(t_mshell *mshell, t_env *env, char *token)
{
	t_expand	data;

	if (expand_data_init(mshell, &data, env, token))
		return (NULL);
	while (token[data.i])
	{
		if (token[data.i] == '$' && token[data.i + 1] && (ft_isalpha(token[data.i + 1]) || token[data.i + 1] == '_' || token[data.i + 1] == '?'))
		{
			data.var_name = extract_var_name(token + data.i + 1, &data.var_len);
			if (data.var_len > 0 && data.var_name)
			{
				data.var_value = fetch_value_from_env(mshell, env, data.var_name);
				if (!data.var_value)
					data.var_value = "";
				data.val_len = ft_strlen(data.var_value);
				ft_memcpy(data.expanded + data.out_i, data.var_value, data.val_len);
				data.out_i += data.val_len;
				data.i += 1 + data.var_len;
				if (ft_strcmp(data.var_name, "?") == 0)
					free(data.var_value);
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

t_token	*expand_token_node(t_mshell *mshell, t_env *env, t_token *node)
{
	char	*expanded;
	char	**split_expand;
	t_token	*chain;
	t_token	*last;

	expanded = expander(mshell, env, node->value);
	if (node->quote_type == NONE && ft_strchr(expanded, ' '))
	{
		split_expand = ft_split(expanded, ' ');
		chain = build_token_chain(split_expand, NONE);
		last = chain;
		while (last && last->next)
			last = last->next;
		if (last)
			last->next = node->next;
		free_tab(split_expand);
		free(expanded);
		return (chain);
	}
	else
	{
		free(node->value);
		node->value = expanded;
	}
	return (node);
}

void	expand_handler(t_mshell *mshell, t_token **lexicon)
{
	t_token	**curr;
	t_token	*expand_chain;

	curr = lexicon;
	while (*curr)
	{
		if ((*curr)->quote_type == SINGLE || (*curr)->type == HERE_DOC_DELIM)
		{
			curr = &((*curr)->next);
			continue ;
		}
		expand_chain = expand_token_node(mshell, mshell->env, *curr);
		if (expand_chain != *curr)
		{
			replace_node_with_chain(lexicon, *curr, expand_chain);
			curr = lexicon;
			continue ;
		}
		curr = &((*curr)->next);
	}
}
