/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collect_or.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:26:46 by tmarion           #+#    #+#             */
/*   Updated: 2025/05/21 16:28:05 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

t_cmd	*new_node;
t_cmd	*tail;

while (lexicon)
{
	new_node = ft_create_node(lexicon, env);
	if (!new_node)
		return ;
	if (!*cmd_list)
		*cmd_list = new_node;
	else
		tail->next = new_node;
	tail = new_node;
	while (lexicon && lexicon->type != PIPE)
		lexicon = lexicon->next;
	if (lexicon && lexicon->type == PIPE)
		lexicon = lexicon->next;
}

void garbage_list_init()