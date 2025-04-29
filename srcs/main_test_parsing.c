/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:57:36 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/29 11:55:31 by tmarion          ###   ########.fr       */
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

t_token	*create_lexicon(char *input, t_parse *parsing)
{
	t_token	*lexicon;
	t_token	*temp;

	if (quote_counter(input) == false)
	{
		printf("There is an odd number of quotes\n");
		return (NULL);
	}
	lexicon = lexer(input, parsing);
	
	temp = lexicon;
	while (temp)
	{
		printf("Value : %s\n Type : %d\n\n", temp->value, temp->type);
		temp = temp->next;
	}
	return (lexicon);
}

static void	readline_loop(char **envp)
{
	char	**split_input;
	t_token	*lexicon;
	t_parse	parsing;

	
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
		lexicon = create_lexicon(parsing.input, &parsing);
		if (parsing(lexicon) == false)//
			break ;
		free(parsing.input);
		free_tab(split_input);
		free_list(lexicon);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)argc;

	catch_sig();
	readline_loop(envp);
	rl_clear_history();
	return (0);
}
