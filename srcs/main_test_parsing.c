/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:57:36 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/03 11:08:34 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>

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

void	create_lexicon(char *input, t_parse *parsing, t_token **lexicon)
{
	// t_token	*temp;

	if (quote_counter(input) == false)
	{
		printf("There is an odd number of quotes\n");
		return ;
	}
	lexer(input, parsing, lexicon);
// 	temp = *lexicon;
// 	while (temp)
// 	{
// 		printf("Value : %s\n Type : %d\n\n", temp->value, temp->type);
// 		temp = temp->next;
// 	}
}

void	readline_loop(char **envp, t_mshell *mshell)
{
	char	**split_input;
	t_token *lexicon;
	t_parse	parsing;

	lexicon = NULL;
	split_input = NULL;
	while (1)
	{
		parsing.input = readline(PROMPT);
		parsing.split_input = ft_split_charset(parsing.input, " ");
		if (!parsing.split_input)
			break ;
		parsing.envp = envp;
		if (!parsing.input)
			break ;
		if (!parsing.input[0])
			continue ;
		add_history(parsing.input);
		//mshell->args = init_exec_args(lexicon);//args dans struct puis exec
		mshell->args = ft_split(parsing.input, ' ');
		mshell->env = builtin_launcher(mshell->args, mshell->env);//
		create_lexicon(parsing.input, &parsing, &lexicon);
		if (parsing_input(lexicon) == false)
			ft_putstr_fd("failed to parse\n", 2);
		exec(lexicon, mshell);
		free(parsing.input);
		free_tab(split_input);
		free_tab(mshell->args);
		free_lexicon(lexicon);
		lexicon = NULL;
	}
}


int	main(int argc, char **argv, char **envp)
{
	t_mshell	mshell;
	
	(void)argv;
	(void)argc;
	mshell.env = NULL;
	mshell.args = NULL;
	catch_sig();
	env_creator(envp, &mshell);
	readline_loop(envp, &mshell);
	rl_clear_history();
	free_list(mshell.env);
	return (0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	(void)argv;
// 	(void)argc;

// 	catch_sig();
// 	readline_loop(envp);
// 	rl_clear_history();
// 	return (0);
// }