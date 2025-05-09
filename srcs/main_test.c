/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:27:42 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/09 16:30:44 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

static	t_bool	init_minishell(t_mshell *mshell)
{
	mshell->env = NULL;
	mshell->args = NULL;
	return (TRUE);
}

static	void	readline_loop(t_mshell *mshell)
{
	char	*input;
	// char	*test_expand;

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
		// test_expand = expand_handler(mshell->env, input + 1); 
		// printf("%s\n", test_expand);
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
