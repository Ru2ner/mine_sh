/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:27:42 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/03 19:37:33 by tlutz            ###   ########.fr       */
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
	struct sigaction sa;
	sa.sa_handler = sigint_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}

static t_env	*builtin_launcher(char **args, t_env *env)
{
	if (args[0] && ft_strcmp(args[0], "env") == 0)
		print_env(env);
	else if (args[0] && ft_strcmp(args[0], "pwd") == 0)
		fetch_cwd(env);
	else if (args[0] && ft_strcmp(args[0], "cd") == 0)
		execute_cd(args[1], env);
	else if (args[0] && ft_strcmp(args[0], "echo") == 0)
		exec_echo(args);
	else if (args[0] && ft_strcmp(args[0], "clear") == 0)
		exec_clear();
	else if (args[0] && ft_strcmp(args[0], "unset") == 0)
		env = exec_unset(env, args[1]);
	else if (args[0] && ft_strcmp(args[0], "export") == 0)
		exec_export(env, args[1]);
	else if (args[0])
		ft_putendl_fd("Command not found", 1);
	return (env);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	const char	*prompt = RED "minishell> " RESET;
	char		**args;
	t_env		*env = NULL;
	
	(void)argv;
	(void)argc;
	catch_sig();
	convert_env_to_list(envp, &env);
	while (1)
	{
		input = readline(prompt);
		if (!input)
			break ;
		add_history(input);
		args = ft_split(input, ' ');
		env = builtin_launcher(args, env);
		free(input);
		free_tab(args);
	}
	free_list(env);
	return (0);
}
