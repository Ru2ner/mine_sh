/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:00:57 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/24 18:52:51 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

void	cleanup_garbage(t_garbage *garbage)
{
	t_garbage	*temp;

	if (!garbage)
		return ;
	while (garbage)
	{
		temp = garbage;
		garbage = garbage->next;
		if (temp->double_p == false && temp->ptr)
			free(temp->ptr);
		else if (temp->double_p == true && temp->dptr)
			free_tab((char **)temp->dptr);
		free(temp);
	}
}

t_garbage	*create_new_garbage_node(void **dptr, void *ptr,t_bool double_p)
{
	t_garbage	*node;

	node = malloc(sizeof(t_garbage));
	ft_memset(node, 0, sizeof(t_garbage));
	if (!node)
		return (malloc_error());
	if (double_p == true)
	{
		node->dptr = dptr;
		node->double_p = true;
	}
	else
	{
		node->ptr = ptr;
		node->double_p = false;
	}
	return (node);
}

void	add_to_garbage(t_garbage **garbage, void **dptr, void *ptr,t_bool double_p)
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

int	main(void)
{
	t_garbage	*garbage;
	char *str = malloc(256);
	char *str2 = malloc(256);
	char **dstr = ft_split("CURSE YOU BAYLE", ' ');
	garbage = NULL;
	
	add_to_garbage(&garbage, NULL, str, false);
	add_to_garbage(&garbage, NULL, str2, false);
	add_to_garbage(&garbage, (void **)dstr, NULL, true);
	cleanup_garbage(garbage);
	return (0);
}
