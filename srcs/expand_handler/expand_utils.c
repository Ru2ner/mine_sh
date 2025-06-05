/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:06:58 by tlutz             #+#    #+#             */
/*   Updated: 2025/06/05 20:25:59 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include "parsing.h"

t_bool	is_valid_for_env_var(char *key)
{
	size_t	i;

	i = 0;
	if (!key || !key[0] || ft_isdigit(key[0]))
		return (FALSE);
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_token	*insert_node(char *value, t_quote_type quote_type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->value = ft_strdup(value);
	new->quote_type = quote_type;
	new->type = WORD;
	new->linked = 0;
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

void	replace_node_with_chain(t_token **lexicon, t_token *curr, t_token \
	*chain)
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
		while (last->next)
			last = last->next;
	if (prev)
		prev->next = chain;
	else
		*lexicon = chain;
	if (last)
		last->next = curr->next;
	if (curr->value)
		free(curr->value);
	free(curr);
}

t_bool	*expand_data_init(t_mshell *mshell, t_expand *data, t_env *env, \
	char *token)
{
	data->i = 0;
	data->out_i = 0;
	data->var_len = 0;
	data->var_name = NULL;
	data->var_value = NULL;
	data->expanded_len = compute_expanded_length(mshell, env, token);
	data->expanded = malloc(data->expanded_len + 1);
	if (!data->expanded)
		return (malloc_error());
	return (NULL);
}
