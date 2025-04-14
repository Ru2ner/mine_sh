/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:00:25 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/14 16:16:49 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <signal.h>

# define DOLLAR_CHAR '$'
# define PIPE_CHAR '|'
# define REDIR_IN_CHAR '<'
# define REDIR_OUT_CHAR '>'
# define HERE_DOC_CHAR "<<"
# define REDIR_OUT_APPEND_CHAR ">>"
# define SINGLE_QUOTE_CHAR '\''
# define DOUBLE_QUOTE_CHAR '\"'
# define SPACE 32
# define H_TAB 9
# define CARR_RETURN 13
# define LINE_FEED 10
# define V_TAB 11
# define FORM_FEED 12

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define BLUE "\033[1;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define RESET "\033[0m"
# define PROMPT "\033[1;31mminishell> \033[0m"

typedef struct s_token	t_token;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HERE_DOC,
	REDIR_OUT_APPEND,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	t_token			*next;
}	t_token;

typedef enum s_bool
{
	false,
	true
}	t_bool;

/****************************Error Handling************************************/




/******************************Tokenizer***************************************/

t_bool	is_special_char(char c);

t_bool	is_whitespaces(char c);

t_bool	is_quote(char c);

char	*extract_quoted_string(char **input);

char	*extract_word(const char **input);

char	*extract_special_char(const char **input);

t_bool	quote_counter(char *input);

t_token	*lexer(const char *input);

void	free_list(t_token *lexicon);

t_token	*create_new_token(char *value, t_token_type type);

void	build_lexicon(t_token **lexicon, char *value, t_token_type type);

/******************************Args Checks*************************************/



#endif