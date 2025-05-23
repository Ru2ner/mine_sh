/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:30:59 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/23 16:24:40 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	if (tab && !*tab)
	{
		free(tab);
		return ;
	}
	while (tab[i])
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	free(tab);
	return ;
}

void	*free_dest(char **dest, int j)
{
	while (j >= 0)
	{
		free(dest[j]);
		j--;
	}
	free(dest);
	return (NULL);
}
