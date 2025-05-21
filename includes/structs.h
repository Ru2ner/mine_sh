/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:20:38 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/21 17:57:59 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdlib.h>

typedef enum e_bool	t_bool;
typedef struct s_keyval	t_keyval;
typedef struct s_env	t_env;
typedef struct s_mshell	t_mshell;
typedef struct s_cmd  t_cmd;
typedef struct s_token	t_token;

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_keyval
{
	char	*key;
	char	*value;
}	t_keyval;

typedef struct s_env
{
	char	*key;
	char	*value;
	t_bool	export;
	t_bool	env;
	t_env	*next;
}	t_env;

typedef struct s_mshell
{
	t_env	*env;
	char	**args;
	t_token	*lexicon;
	t_cmd	*exec_list;
	int		exit_status;
}	t_mshell;

typedef struct s_cmd
{
	char	**args;
	char	*infile;
	char	*outfile;
	t_bool	append;
	t_bool	pipe;
	char	*heredoc_delim;
	t_cmd	*next;
}	t_cmd;

typedef enum e_special_types
{
	FD,
	FOLDER,
	CMD,
	CMD_ARGS,
	SEMICOLON,
}	t_special_types;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	INFILE,
	REDIR_OUT,
	OUTFILE,
	REDIR_OUT_APPEND,
	OUTFILE_APPEND,
	HERE_DOC,
	HERE_DOC_DELIM
}	t_token_type;

typedef enum e_quote_type
{
	NONE,
	SINGLE,
	DOUBLE
}	t_quote_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	t_quote_type	quote_type;
	t_bool			link;
	t_token			*next;
}	t_token;

typedef struct s_parse
{
	char	*input;
	char	**split_input;
	char	**envp;
}	t_parse;

typedef struct s_exec
{
	int		prev_fd;
	int		pipe_fd[2];
	char	**envp;
	int		status;
	t_cmd	*cmd_list;
	t_token	*lexicon;
}	t_exec;

typedef struct s_expand
{
	char	*var_name;
	char	*var_value;
	char	*expanded;
	size_t	expanded_len;
	size_t	var_len;
	size_t	val_len;
	size_t	i;
	size_t	out_i;
}	t_expand;

#endif