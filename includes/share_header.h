/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   share_header.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 10:08:24 by tmarion           #+#    #+#             */
/*   Updated: 2025/05/09 12:27:37 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARE_HEADER_H
# define SHARE_HEADER_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>

typedef struct s_token	t_token;
typedef struct s_env	t_env;

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
	ERROR//15
}	t_token_type;

typedef enum s_bool
{
	false,
	true
}	t_bool;

typedef struct s_env
{
	char	*key;
	char	*value;
	t_bool	export;
	t_bool	env;
	t_env	*next;
}	t_env;

typedef struct s_token
{
	char			*value;
	int				index;
	t_token_type	type;
	t_token			*next;
}	t_token;

typedef struct t_mshell
{
	t_env	*env;
	char	**args;
	t_token	*lexicon;// --> t_cmd
}	t_mshell;



void	free_tab(char **tab);

int 	exec(t_token *lexicon);

#endif
