/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:41:49 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/03 15:59:10 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

void	exec_echo(char **args)
{
	size_t	i;
	size_t	tab_size;
	bool	n_option;

	i = 1;
	n_option = false;
	if (ft_strcmp(args[1], "-n") == 0)
	{
		n_option = true;
		i = 2;
	}
	tab_size = get_tab_size(args);
	while (args[i])
	{
		printf("%s", args[i]);
		if (i < tab_size - 1)
			printf(" ");
		i++;
	}
	if (n_option == false)
		printf("\n");
}
