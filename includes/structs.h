/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:20:38 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/07 13:42:48 by tlutz            ###   ########.fr       */
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
	// t_token	*lexicon; --> t_cmd
}	t_mshell;

typedef struct s_cmd
{
	char	**args; // Cmd dans le slot 0 et arguments ensuite
	char	*infile; // Ou fd si on peut open plus tôt dans le programme
	char	*outfile; // idem
	t_bool	append; // true pour >> false pour >
	t_bool	pipe; // si pipe ensuite
	char	*heredoc; // Delimiter pour le here_doc, si besoin
	t_cmd	*next;
}	t_cmd;

#endif