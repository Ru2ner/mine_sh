/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:41:49 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/27 14:35:59 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

static void	arg_checker(char **args, t_bool *n_option, size_t *i)
{
	size_t	j;

	j = 0;
	if (!args || !*args)
		return ;
	while (args[j])
		j++;
	if (j == 0)
		return ;
	j = 1;
	if (args[1] && args[1][0] == '-' && args[1][1] == 'n')
	{
		while (args[1][j] == 'n')
			j++;
		if (args[1][j] == '\0')
		{
			*n_option = TRUE;
			*i = 2;
		}
	}
}

void	exec_echo(char **args)
{
	size_t	i;
	size_t	tab_size;
	t_bool	n_option;

	i = 1;
	n_option = FALSE;
	arg_checker(args, &n_option, &i);
	tab_size = get_tab_size(args);
	while (args[i])
	{
		printf("%s", args[i]);
		if (i < tab_size - 1)
			printf(" ");
		i++;
	}
	if (n_option == FALSE)
		printf("\n");
}
