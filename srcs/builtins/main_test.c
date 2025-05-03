/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:27:42 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/03 10:48:57 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include <signal.h>

static void	sigint_handler(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	catch_sig(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}

static	void	readline_loop(t_mshell *mshell)
{
	char	*input;

	while (1)
	{
		input = readline(PROMPT);
		if (!input)
			break ;
		if (!*input)
			continue ;
		add_history(input);
		mshell->args = ft_split(input, ' ');
		mshell->env = builtin_launcher(mshell->args, mshell->env);
		free(input);
		free_tab(mshell->args);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_mshell	mshell;

	(void)argv;
	(void)argc;
	catch_sig();
	init_minishell(&mshell);
	env_creator(envp, &mshell);
	readline_loop(&mshell);
	rl_clear_history();
	free_list(mshell.env);
	return (0);
}
