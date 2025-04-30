/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:04:35 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/30 15:40:00 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

void	free_lexicon(t_token *lexicon)
{
	t_token	*temp;

	if (!lexicon)
		return ;
	while (lexicon)
	{
		temp = lexicon;
		lexicon = lexicon->next;
		if (temp->value)
		{
			free(temp->value);
			temp->value = NULL;
		}
		if (temp)
		{
			free(temp);
			temp = NULL;
		}
	}
}

size_t	get_lexicon_size(t_token *lexicon)
{
	size_t	i;

	i = 0;
	if (!lexicon)
		return (-1);
	while (lexicon)
	{
		i++;
		lexicon = lexicon->next;
	}
	return (i);
}

t_token	*create_new_token(char *value, t_token_type type)
{
	t_token	*token;
	
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	if (!token->value)
		return (NULL);
	token->type = type;
	token->next = NULL;
	return (token);
}

void	build_lexicon(t_token **lexicon, char *value, t_token_type type)
{
	t_token	*new_token;
	t_token	*temp;

	new_token = create_new_token(value, type);
	if (!new_token)
		return ;
	if (!*lexicon)
	{
		*lexicon = new_token;
		return ;
	}
	temp = *lexicon;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_token;
}
