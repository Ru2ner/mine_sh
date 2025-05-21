/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_msgs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:57:48 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/21 13:45:01 by tlutz            ###   ########.fr       */
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

void	*cmd_not_found_error(void)
{
	ft_putendl_fd("Command not found", 2);
	return (NULL);
}

void	*invalid_env_var(void)
{
	ft_putendl_fd("key is not a valid identifier", 2);
	return (NULL);
}
