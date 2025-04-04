/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:07:12 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/04 19:48:02 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

static t_token_type	identify_quotes(const char c)
{
	if (c == SINGLE_QUOTE_CHAR)
		return (SINGLE_QUOTE);
	else if (c == DOUBLE_QUOTE_CHAR)
		return (DOUBLE_QUOTE);
	return (WORD);
}

static t_token_type	identify_special_char(const char *token)
{
	if (ft_strcmp(token, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(token, "<") == 0)
		return (REDIR_IN);
	else if (ft_strcmp(token, ">") == 0)
		return (REDIR_OUT);
	else if (ft_strcmp(token, "<<") == 0)
		return (HERE_DOC);		
	else if (ft_strcmp(token, ">>") == 0)
		return (REDIR_OUT_APPEND);
	else if (ft_strcmp(token, "'") == 0)
		return (SINGLE_QUOTE);
	else if (ft_strcmp(token, "\"") == 0)
		return (DOUBLE_QUOTE);
	return (WORD);
}

static void	append_to_list(t_token **head, t_token **curr, t_token *new_token)
{
	if (!*head)
	{
		*head = new_token;
		*curr = new_token;
	}
	else
	{
		(*curr)->next = new_token;
		*curr = new_token;
	}
}

t_token	*lexer(const char *input)
{
	t_token	*head;
	t_token	*curr;
	t_token	*new_token;

	head = NULL;
	curr = NULL;
	while (*input)
	{
		if (is_whitespaces(*input))
		{
			input++;
			continue ;
		}
		new_token = malloc(sizeof(t_token));
		if (is_special_char(*input))
		{
			new_token->value = extract_special_char(&input);
			new_token->type = identify_special_char(new_token->value);
		}
		else if (is_quote(*input))
		{
			new_token->type = identify_quotes(*input);
			new_token->value = extract_quoted_string((char **)&input);
		}
		else
		{
			new_token->value = extract_word(&input);
			new_token->type = WORD;
		}
		append_to_list(&head, &curr, new_token);
	}
	return (head);
}

int	main(void)
{
	char	input[] = "$USER";
	t_token	*lexicon;

	lexicon = lexer(input);
	while (lexicon)
	{
		printf("Value : %s\n Type : %d\n\n", lexicon->value, lexicon->type);
		lexicon = lexicon->next;
	}
	return (0);
}