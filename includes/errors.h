/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:57:58 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/21 18:29:39 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "exec.h"

# define NOSUCHFILEORDIR 0
# define NOPERMS 1
# define NOTADIR 2
# define HOMENOTSET 3
# define HOME_ERR_STR "minishell : cd: HOME not set"

typedef struct s_garbage	t_garbage;
typedef struct s_garbage
{
	void		**dptr;
	void		*ptr;
	t_bool		double_p;
	t_garbage	*next;
}	t_garbage;

typedef struct s_trash		t_trash;
typedef struct s_trash
{
	char	**adr;
	t_bool	tab;
	t_trash	*next;
}	t_trash;


void	*cd_error(int errnum);

void	*malloc_error(void);

void	*cmd_not_found_error(void);

void	*invalid_env_var(void);

/*****************************Garbage Collector****************************************/

t_trash	*garbage_list_init(void);

void 	append_trash(t_trash *trash, char **ptr, t_bool bat);

void 	trash_cleaner(t_trash *trash);


#endif