/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:41:07 by tmarion           #+#    #+#             */
/*   Updated: 2025/05/21 15:51:40 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

// char	*expand_variables(t_env *env, char *input)
// {
// 	size_t	len;
// 	char	*result;
	
// 	len = ft_strlen(input);
// 	result = malloc(len + 1);
// 	if (!result)
// 		return (malloc_error());
	
// }

char	*expand_finder(t_env *env, char *key)
{
	t_env	*temp;
	char	*expanded;
	
	temp = env;
	if (key[0] == '$')
	key++;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0 && temp->value)
		{
			expanded = ft_strdup(temp->value);
			if (!expanded)
				return (malloc_error());
			return (expanded);
		}
		temp = temp->next;
	}
	expanded = ft_strdup("");
	if (!expanded)
		return (malloc_error());
	return (expanded);
}

void	expand_handler(t_env *env, t_token *lexicon)
{
	t_token	*temp;
	char	*expanded;

	temp = lexicon;
	while (temp)
	{
		if (temp->type == WORD && temp->quote_type != SINGLE)
		{
			expanded = expand_finder(env, temp->value);
			if (!expanded)
				return ;
			free(temp->value);
			temp->value = expanded;
		}
		temp = temp->next;
	}
}
