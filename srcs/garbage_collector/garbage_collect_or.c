/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collect_or.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:26:46 by tmarion           #+#    #+#             */
/*   Updated: 2025/05/26 15:21:50 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

char **str_to_tab(char *s)
{
	char **tab;
	int	i = 0;

	tab = malloc(sizeof(char *) * 2);
	if (!tab || !s)
		return (NULL);
	tab[0] = s;
	tab[1] = NULL;
	while (tab[i])
		i++;
	return (tab);
}

void trash_cleaner(t_trash *trash)
{
	t_trash	*temp;
	int		i;

	i = 0;
	temp = trash;
	if (!trash)
		return ;
	while (trash)
	{
		if (!trash->adr && trash->next)
			continue ;
		print_tab(trash->adr);
		free_tab(trash->adr);
		trash = trash->next;
	}
	trash = temp;
	while (trash)
	{
		temp = trash->next;
		free(trash);
		trash = temp;
	}
}

void append_trash(t_trash *trash, char **ptr)
{
	t_trash	*new;

	if (!ptr || !trash)
		return ;
	if (!trash->adr)
		trash->adr = ptr;
	else
	{
		new = malloc(sizeof(t_trash));
		if (!new)
			return ;
		ft_memset(new, 0, sizeof(t_trash));
		while (trash->next)
			trash = trash->next;
		trash->next = new;
		new->adr = ptr;
	}
}

t_trash *garbage_list_init(void)
{
	t_trash *trash;
	
	trash = malloc(sizeof(t_trash));
	if (!trash)
		return (NULL);
	ft_memset(trash, 0, sizeof(t_trash));
	// trash->adr = NULL;
	// trash->tab = FALSE;
	// trash->next = NULL;
	return (trash);
}