
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:42:01 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/01 16:11:17 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

void	print_env(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	if (!*envp)
		return ;
	while (envp[i])
	{
		ft_putendl_fd(envp[i], 1);
		i++;
	}
}
