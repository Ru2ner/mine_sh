/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_msgs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:57:48 by tlutz             #+#    #+#             */
/*   Updated: 2025/06/05 15:56:36 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "libft.h"
#include "string.h"

void	*malloc_error(void)
{
	strerror(ENOMEM);
	return (NULL);
}

int	malloc_error_int(void)
{
	strerror(ENOMEM);
	return (1);
}

void	*cd_error(int errnum)
{
	if (errnum == NOSUCHFILEORDIR)
		strerror(ENOENT);
	if (errnum == NOPERMS)
		strerror(EACCES);
	if (errnum == NOTADIR)
		strerror(ENOTDIR);
	if (errnum == HOMENOTSET)
		ft_putendl_fd(HOME_ERR_STR, 2);
	return (NULL);
}

void	*cmd_not_found_error(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (NULL);
}

int	invalid_env_var(char *arg)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
	return (1);
}
