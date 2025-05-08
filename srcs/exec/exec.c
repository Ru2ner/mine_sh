/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:08:09 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/08 13:09:44 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include <signal.h>

int exec(t_token *lexicon, t_mshell *mshell)
{
	int i = 0;

	while (lexicon)
	{
		printf("LEXICON//	value: %s \n token: %d \n index: %d \n\n", lexicon->value, lexicon->type, lexicon->index);
		lexicon = lexicon->next;
	}
	while (mshell->args[i])
	{
		printf("MSHELL//	args: %s\n", mshell->args[i]);
		i++;
	}
	return (1);
}

// t_cmd *ft_create_node(t_cmd *cmd_list, t_token *lexicon)// t_token *lexicon
// {
// 	t_cmd *new_node;
// 	t_cmd *curent_node;

// 	curent_node = NULL;
// 	new_node = malloc(sizeof(t_cmd));
// 	if (!new_node)
// 		return (0);
//     //initialiser
// 	if (cmd_list == NULL)
// 	// 	a->top = new_node; linker prochain noeud si premier
// 	else
// 	{
// 		// curent_node = a->top; linker tout les noeuds ensemble si premier existe deja
// 		// while (curent_node->next != NULL)
// 		// 	curent_node = curent_node->next;
// 		// curent_node->next = new_node;
// 	}
// 	return (1);
// }

// t_cmd *create_exec_list(t_cmd *cmd_list)
// {
// 	cmd_list = malloc(sizeof(t_cmd));
//     if (!cmd_list)
//         return (NULL);
//     return (cmd_list);
// }