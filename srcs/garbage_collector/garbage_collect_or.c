/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collect_or.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:26:46 by tmarion           #+#    #+#             */
/*   Updated: 2025/05/21 20:02:34 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

static void	cleanup_garbage(t_trash *garbage)
{
	t_trash	*temp;

	if (!garbage)
		return ;
	while (garbage)
	{
		temp = garbage;
		garbage = garbage->next;
		free(temp);
	}
}

void trash_cleaner(t_trash *trash)
{
	t_trash	*temp;
	int		i;
	char	**ptr;

	i = 0;
	temp = trash;
	while (temp)
	{
		ptr = temp->adr;
		if (temp->tab == FALSE && ptr)
		{
			free(*ptr);
			*ptr = NULL;
			printf("free de string\n\n");
		}
		else
		{
			if (!ptr)
			{
				printf("probleme\n\n");
				temp = temp->next;
				continue ;
			}
			free_tab(ptr);
			printf("free de tab\n\n");
		}
		temp = temp->next;
	}
	cleanup_garbage(trash);
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
		ft_memset(new, 0, sizeof(t_trash));
		while (trash->next)
			trash = trash->next;
		trash->next = new;
		new->adr = ptr;
		new->tab = bat;
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