/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:30:59 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/10 19:49:36 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	*free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab || !*tab)
		return (NULL);
	while (tab[i])
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
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
