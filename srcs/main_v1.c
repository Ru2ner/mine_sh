/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_v1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:57:10 by tlutz             #+#    #+#             */
/*   Updated: 2025/06/04 19:42:28 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include "exec.h"
#include "parsing.h"
#include "libft.h"

static	t_bool	init_minishell(t_mshell *sh)
{
	sh->env = NULL;
	sh->lexicon = NULL;
	sh->exec_list = NULL;
	sh->exit_status = 0;
	sh->g_collector = NULL;
	sh->prompt = NULL;
	sh->env_tab = NULL;
	sh->input = NULL;
	return (TRUE);
}

t_bool	create_lexicon(char *input, t_mshell *sh)
{
	if (are_quotes_balanced(input) == FALSE)
	{
		printf("There is an odd number of quotes\n");
		return (FALSE);
	}
	if (parsing_input(sh->lexicon) == FALSE)
	{
		ft_putstr_fd("syntax error\n", 2);
		return (FALSE);
	}
	lexer(input, &sh->lexicon);
	expand_handler(sh, &sh->lexicon);
	if (DEBUG == 1)
		print_lexer(sh->lexicon);
	return (TRUE);
}

void	readline_loop(t_mshell *sh)
{
	while (1)
	{
		sh->lexicon = NULL;
		sh->g_collector = NULL;
		sh->prompt = create_prompt(sh->env);
		add_to_garbage(&sh->g_collector, NULL, (void *)sh->prompt, FALSE);
		sh->input = readline(sh->prompt);
		add_to_garbage(&sh->g_collector, NULL, (void *)sh->input, FALSE);
		if (!sh->input)
			break ;
		if (!sh->input[0])
		{
			cleanup_garbage(sh->g_collector);
			sh->g_collector = NULL;
			continue ;
		}
		add_history(sh->input);
		if (create_lexicon(sh->input, sh) == FALSE)
			continue ;
		sh->env_tab = convert_env_to_tab(sh->env);
		cleanup_garbage(sh->g_collector);
		exec(&sh->lexicon, sh);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_mshell	sh;

	if (argc != 1)
	{
		ft_putendl_fd("minishell does not handle launch arguments", 2);
		return (1);
	}
	(void)argv;
	init_minishell(&sh);
	env_creator(envp, &sh);
	catch_sig();
	readline_loop(&sh);
	cleanup_minishell(&sh);
	rl_clear_history();
	return (0);
}
