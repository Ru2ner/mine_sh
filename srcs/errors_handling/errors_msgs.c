/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_msgs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:57:48 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/10 16:13:10 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

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
	return (NULL);
}
