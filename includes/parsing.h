/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:00:25 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/18 13:45:30 by tmarion          ###   ########.fr       */
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
	WORD,//0
	PIPE,//1
	REDIR_IN,//2
	REDIR_OUT,//3
	HERE_DOC,//4
	REDIR_OUT_APPEND,//5
	SINGLE_QUOTE,//6
	DOUBLE_QUOTE,//7
	FILE_DESCRIPTOR,////8
	FOLDER,//9
	CMD,//10
	CMD_ARGS,//11
	SEMICOLON//12
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

typedef struct s_parse
{
	char	**split_input;
	char	**envp;
}	t_parse;

/****************************Error Handling************************************/




/******************************Tokenizer***************************************/

t_bool	is_special_char(char c);

t_bool	is_whitespaces(char c);

t_bool	is_quote(char c);

char	*extract_quoted_string(char **input);

char	*extract_word(const char **input);

char	*extract_special_char(const char **input);

t_bool	quote_counter(char *input);

t_token	*lexer(const char *input, t_parse *pasring);

t_token	*create_new_token(char *value, t_token_type type);

void	build_lexicon(t_token **lexicon, char *value, t_token_type type);

/******************************Args Checks*************************************/

/******************************free_stuff*************************************/

void	free_tab(char **tab);

void	free_list(t_token *lexicon);



#endif