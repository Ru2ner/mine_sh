/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:23:49 by tlutz             #+#    #+#             */
/*   Updated: 2025/06/05 16:26:26 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	print_lexer(t_token *lexicon)
{
	t_token	*temp;

	temp = lexicon;
	printf("------------------Lexer----------------------------------------\n");
	while (temp)
	{
		printf("value: %s\n", temp->value);
		printf("type: %d\n", temp->type);
		printf("quote type: %d\n", temp->quote_type);
		printf("link: %d\n\n", temp->linked);
		temp = temp->next;
	}
	printf("-------------------------------------------------------------\n\n");
}

void	print_cmd_details(t_cmd *cmd)
{
	printf("infile: %s \n", cmd->infile);
	printf("outfile: %s \n", cmd->outfile);
	printf("append: %d \n", cmd->append);
	printf("pipe: %d \n", cmd->pipe);
	printf("heredoc: %s \n", cmd->heredoc_delim);
}

void	print_exec_list(t_cmd *cmd_list)
{
	int		i;
	t_cmd	*temp;

	i = 0;
	temp = cmd_list;
	printf("------------------Exec List------------------------------------\n");
	while (temp)
	{
		i = 0;
		if (temp->args != NULL)
		{
			while (temp->args[i])
			{
				printf("args: %s \n", temp->args[i]);
				i++;
			}
		}
		print_cmd_details(temp);
		temp = temp->next;
	}
	printf("-------------------------------------------------------------\n\n");
}
