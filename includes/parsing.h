/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:00:25 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/04 19:08:25 by tlutz            ###   ########.fr       */
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
# include <stdbool.h>

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
	struct s_token	*next;
}	t_token;

/****************************Error Handling************************************/




/******************************Tokenizer***************************************/

bool	is_special_char(char c);

bool	is_whitespaces(char c);

bool	is_quote(char c);

char	*extract_quoted_string(char **input);

/******************************Args Checks*************************************/



#endif