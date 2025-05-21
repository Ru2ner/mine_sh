/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collect_or.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:26:46 by tmarion           #+#    #+#             */
/*   Updated: 2025/05/21 18:23:02 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

void trash_cleaner(t_trash *trash)
{
	int	i;

	i = 0;
	while (trash)
	{
		if (trash->tab == FALSE)
		{
			free(trash->adr);
			trash->adr = NULL;
			printf("free de string\n\n");
		}
		else
		{
			if (!trash->adr || trash->adr[i])
			{
				printf("probleme\n\n");
				return ;
			}
			while (trash->adr[i])
			{
				free(trash->adr[i]);
				i++;
			}
			free(trash->adr);
			trash->adr = NULL;
			printf("free de tab\n\n");
		}
		trash = trash->next;
	}
}

void append_trash(t_trash *trash, char **ptr, t_bool bat)
{
	t_trash	*new;

	if (!ptr || !trash)
		return ;
	if (!trash->adr)
	{
		trash->adr = ptr;
		trash->tab = bat;
	}
	else
	{
		new = malloc(sizeof(t_trash));
		if (!new)
			return ;
		while (trash->next)
			trash = trash->next;
		trash->next = new;
		new->adr = ptr;
		new->tab = bat;
		new->next = NULL;
	}
}

t_trash *garbage_list_init(void)
{
	t_trash *trash;
	
	trash = malloc(sizeof(t_trash));
	if (!trash)
		return (NULL);
	trash->adr = NULL;
	trash->tab = FALSE;
	trash->next = NULL;
	return (trash);
}