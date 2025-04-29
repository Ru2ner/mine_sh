/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:07:12 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/29 17:09:21 by tmarion          ###   ########.fr       */
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
	else if (ft_strcmp(token, ";") == 0)
		return (SEMICOLON);
	return (WORD);
}


static t_token_type	specify_each_words(char *value, t_parse *parsing)
{
	struct	stat	type;
	char			**paths;

	if (!value || !parsing)
		return (ERROR);
	paths = get_paths(parsing->envp);
	lstat(value, &type);
	if (cmd_path(value, paths))
	{
		free_tab(paths);
		return (CMD);
	}
	else if (S_ISDIR(type.st_mode))
	{
		free_tab(paths);
		return (FOLDER);
	}
	else if (S_ISREG(type.st_mode))
	{
		free_tab(paths);
		return (FD);
	}
	return (WORD);
}

void	identify_redir_file(t_token *lexicon)
{
	int	i;

	i = 0;
	while (lexicon->next)
	{
		if (lexicon->type == FD && i == 0)
		{
			lexicon->type = INFILE;
			i++;
		}
		if (lexicon->type == REDIR_OUT && lexicon->next->type == FD)
			lexicon->next->type = OUTFILE;
		lexicon = lexicon->next;
	}
}


t_token	*lexer(const char *input, t_parse *parsing, t_token **lexicon)
{
	t_token_type	type;
	char			*value;

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
			value = extract_quoted_string((char **)input);
		}
		else
		{
			value = extract_word(&input);
			type = specify_each_words(value, parsing);
			if (is_builtin(value))
				type = CMD;
		}
		build_lexicon(lexicon, value, type);
	}
	if (is_pipe(*lexicon) || is_redir(*lexicon))
		identify_redir_file(*lexicon);
	return (*lexicon);
}
