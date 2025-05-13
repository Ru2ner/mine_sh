/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:20:38 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/13 13:37:31 by tlutz            ###   ########.fr       */
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
	FD,////8
	FOLDER,//9
	CMD,//10
	CMD_ARGS,//11
	SEMICOLON,//12
	INFILE,//13
	OUTFILE,//14
	ERROR,//15
	HERE_DOC_DELIM,
	OUTFILE_APPEND
}	t_token_type;

typedef struct s_token
{
	char			*value;
	int				index;
	t_token_type	type;
	t_token			*next;
}	t_token;

typedef struct s_parse
{
	char	*input;
	char	**split_input;
	char	**envp;
}	t_parse;

#endif