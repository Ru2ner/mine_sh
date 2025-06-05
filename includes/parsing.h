/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:00:25 by tlutz             #+#    #+#             */
/*   Updated: 2025/06/05 16:08:30 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "structs.h"
# include "exec.h"
# include "libft.h"

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

void			readline_loop(t_mshell *mshell);

t_bool			is_special_char(char c);

t_bool			is_whitespaces(char c);

t_bool			is_quote(char c);

t_bool			is_builtin(char *str);

t_bool			is_pipe(t_token *lexicon);

t_bool			is_redir(t_token *lexicon);

char			*extract_quoted_string(char **input);

char			*extract_word(char **input);

char			*extract_special_char(char **input);

void			lexer(char *input, t_token **lexicon);

t_token			*create_new_token(char *value, t_lex_helper *tok_content);

void			build_lexicon(t_token **lexicon, char *value, \
	t_lex_helper *tok_content);

t_bool			parsing_input(t_token *lexicon);

void			expand_handler(t_mshell *mshell, t_token **lexicon);

t_bool			is_valid_for_env_var(char *key);

t_token			*build_token_chain(char **split, t_quote_type quote_type);

void			replace_node_with_chain(t_token **lexicon, t_token *curr, \
	t_token *chain);

t_token			*insert_node(char *value, t_quote_type quote_type);

t_quote_type	identify_quotes(const char c);

t_token_type	identify_special_char(const char *input);

void			identify_redir_file(t_token *lexicon);

t_bool			*expand_data_init(t_mshell *mshell, t_expand *data, \
	t_env *env, char *token);

size_t			compute_expanded_length(t_mshell *mshell, t_env *env, \
	char *token);

char			*extract_var_name(char *str, size_t *var_len);

char			*expander(t_mshell *mshell, t_env *env, char *token);

t_token			*expand_token_node(t_mshell *mshell, t_env *env, t_token *node);
/******************************Args Checks*************************************/

char			**get_paths(char **env);

char			**cmd_arg(char *cmd);

char			*cmd_path(char *cmd, char **path);

/******************************utils_stuff*************************************/

void			free_lexicon(t_token *lexicon);

void			env_creator(char **envp, t_mshell *mshell);

t_bool			quote_counter(char *input, size_t i);

t_bool			are_quotes_balanced(char *input);

#endif