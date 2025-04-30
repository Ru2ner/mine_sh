/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:57:58 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/24 19:02:48 by tlutz            ###   ########.fr       */
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

void	*cd_error(int errnum);

void	*malloc_error(void);

#endif