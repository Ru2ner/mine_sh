/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:00:25 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/20 15:20:41 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "structs.h"
# include "exec.h"

# define DOLLAR_CHAR '$'
# define PIPE_CHAR '|'
# define REDIR_IN_CHAR '<'
# define REDIR_OUT_CHAR '>'
# define HERE_DOC_CHAR "<<"
# define REDIR_OUT_APPEND_CHAR ">>"
# define SINGLE_QUOTE_CHAR '\''
# define DOUBLE_QUOTE_CHAR '\"'
# define SPACE_CHAR 32
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

/******************************Tokenizer***************************************/

void	readline_loop(t_mshell *mshell);

t_bool	is_special_char(char c);

t_bool	is_whitespaces(char c);

t_bool	is_quote(char c);

t_bool	is_builtin(char *str);

t_bool	is_pipe(t_token *lexicon);

t_bool	is_redir(t_token *lexicon);

char	*extract_quoted_string(char **input);

char	*extract_word(char **input);

char	*extract_special_char(char **input);

t_bool	quote_counter(char *input);

void	lexer(char *input, t_token **lexicon);

t_token	*create_new_token(char *value, t_token_type type, t_quote_type quote_type, t_bool link);

void	build_lexicon(t_token **lexicon, char *value, t_token_type type, t_quote_type quote_type, t_bool link);

t_bool	parsing_input(t_token *lexicon);

char	*expand_handler(t_env *env, char *key);

/******************************Args Checks*************************************/

char	**get_paths(char **env);

char	**cmd_arg(char *cmd);

char	*cmd_path(char *cmd, char **path);

/******************************utils_stuff*************************************/

void	free_lexicon(t_token *lexicon);

void	env_creator(char **envp, t_mshell *mshell);

t_bool	quote_counter(char *input);

#endif