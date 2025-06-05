/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:00:57 by tlutz             #+#    #+#             */
/*   Updated: 2025/06/05 16:53:53 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab || !*tab)
		return ;
	dprintf(2, "print{start}\n\n");
	while (tab[i])
	{
		dprintf(2, "current:%s\n", tab[i]);
		i++;
	}
	dprintf(2, "\n\nprint{end}\n\n");
	return ;
}

void	cleanup_garbage(t_garbage *garbage)
{
	t_garbage	*temp;

	if (!garbage)
		return ;
	while (garbage)
	{
		temp = garbage;
		garbage = garbage->next;
		if (temp->double_p == FALSE && temp->ptr)
			free(temp->ptr);
		else if (temp->double_p == TRUE && temp->dptr)
			free_tab((char **)temp->dptr);
		free(temp);
	}
}

t_garbage	*create_new_garbage_node(void **dptr, void *ptr, t_bool double_p)
{
	t_garbage	*node;

	node = malloc(sizeof(t_garbage));
	ft_memset(node, 0, sizeof(t_garbage));
	if (!node)
		return (malloc_error());
	if (double_p == TRUE)
	{
		node->dptr = dptr;
		node->double_p = TRUE;
	}
	else
	{
		node->ptr = ptr;
		node->double_p = FALSE;
	}
	return (node);
}

void	add_to_garbage(t_garbage **garbage, void **dptr, void *ptr, \
	t_bool double_p)
{
	t_garbage	*temp;
	t_garbage	*new_node;

	new_node = create_new_garbage_node(dptr, ptr, double_p);
	if (!new_node)
		return ;
	if (!*garbage)
	{
		*garbage = new_node;
		return ;
	}
	temp = *garbage;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
}
