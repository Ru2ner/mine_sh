/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:07:12 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/18 14:01:40 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
//////////////////////////////
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

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


static t_token_type what_is_this(t_parse *parsing)
{
		(void)parsing;
	// struct stat type;
	// int			i;

	// i = 0;

	// while (parsing->split_input[i])
	// {
	// 	printf("split: %s\n", parsing->split_input[i]);
	// 	i++;
	// }
	// i = 0;
	// while (parsing->envp[i])
	// {
	// 	printf("env: %s\n", parsing->envp[i]);
	// 	i++;
	// }
	// while (token[i])
	// {
	// 	if (lstat(token[i], &type) == -1)
	// 		return (WORD);
	// 	if (S_ISDIR(type.st_mode))
	// 		return (FOLDER);
	// 	else if (S_ISREG(type.st_mode))
	// 		return (FILE_DESCRIPTOR);
	// 	else if (access(token[i], W_OK))//absolute path -> pipex FIX
	// 		return (CMD);
	// 	else
	// 		return (WORD);
	// 	i++;
	// }
	return (WORD);
}


t_token	*lexer(const char *input, t_parse *parsing)
{
	t_token			*lexicon;
	t_token_type	type;
	char			*value;

	lexicon = malloc(sizeof(t_token));
	ft_memset(lexicon, 0, sizeof(t_token));
	while (*input)
	{
		if (is_whitespaces(*input))
		{
			input++;
			continue ;
		}
		if (is_special_char(*input))
		{
			value = extract_special_char(&input);
			type = identify_special_char(value);
		}
		else if (is_quote(*input))
		{
			type = identify_quotes(*input);
			value = extract_quoted_string((char **)&input);
		}
		else
		{
			value = extract_word(&input);
			type = what_is_this(parsing);
			type = WORD;
		}
		build_lexicon(&lexicon, value, type);
	}
	return (lexicon);
}
