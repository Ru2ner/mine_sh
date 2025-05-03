/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:08:09 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/03 11:08:23 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include <signal.h>

// init_exec_args

int exec(t_token *lexicon, t_mshell *mshell)
{
	int i = 0;

	while (lexicon)
	{
		printf("LEXICON//	value: %s \n token: %d \n\n", lexicon->value, lexicon->type);
		lexicon = lexicon->next;
	}
	while (mshell->args[i])
	{
		printf("MSHELL//	args: %s\n", mshell->args[i]);
		i++;
	}
	return (1);
}