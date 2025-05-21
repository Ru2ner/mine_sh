/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:20:38 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/21 17:54:07 by tmarion          ###   ########.fr       */
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


#endif

/*int	ft_create_node(t_stack *a, int value)
{
	t_node	*new_node;
	t_node	*curent_node;

	curent_node = NULL;
	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return (0);
	new_node->value = value;
	new_node->bin_value = ft_binary_convert(value);
	new_node->next = NULL;
	if (a->top == NULL)
		a->top = new_node;
	else
	{
		curent_node = a->top;
		while (curent_node->next != NULL)
			curent_node = curent_node->next;
		curent_node->next = new_node;
	}
	return (1);
}

t_stack	*ft_init_stack(void)
{
	t_stack	*stack;

	stack = (t_stack *)malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->top = NULL;
	return (stack);
}

int	creat_all(t_stack *a, char **value, int i)
{
	if (!value || !a)
		return (0);
	while (value[i])
	{
		if (ft_create_node(a, ft_atoi(value[i])) == 0)
			return (0);
		i++;
	}
	a->size = i;
	a->moove = 0;
	if (push_parser(a, value) == 0)
		return (0);
	return (1);
}*/