/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_msgs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:57:48 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/07 13:36:18 by tlutz            ###   ########.fr       */
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
