/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:57:36 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/14 16:36:35 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
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

t_token	*create_lexicon(char *input)
{
	t_token	*lexicon;
	t_token	*temp;

	if (quote_counter(input) == false)
	{
		printf("There is an odd number of quotes\n");
		return (NULL);
	}
	lexicon = lexer(input);
	temp = lexicon;
	while (temp)
	{
		printf("Value : %s\n Type : %d\n\n", temp->value, temp->type);
		temp = temp->next;
	}
	return (lexicon);
}

static void	readline_loop()
{
	char	*input;
	t_token	*lexicon;

	while (1)
	{
		input = readline(PROMPT);
		if (!input)
			break ;
		if (!*input)
			continue ;
		add_history(input);
		lexicon = create_lexicon(input);
		free(input);
		free_list(lexicon);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)argc;
	(void)envp;

	catch_sig();
	readline_loop();
	rl_clear_history();
	return (0);
}
