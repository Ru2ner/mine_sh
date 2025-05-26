/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_v1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:57:10 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/26 14:51:17 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <readline/readline.h>
#include <readline/history.h>
#include "exec.h"
#include "parsing.h"
#include "libft.h"

static	t_bool	init_minishell(t_mshell *mshell)
{
	mshell->env = NULL;
	mshell->args = NULL;
	return (TRUE);
}

t_bool	create_lexicon(char *input, t_mshell *mshell, t_token **lexicon)
{
	(void)mshell;
	if (quote_counter(input) == FALSE)
	{
		printf("There is an odd number of quotes\n");
		return (FALSE);
	}
	lexer(input, lexicon);

	t_token	*temp;
	temp = *lexicon;
	printf("------------------Lexer-----------------------------------------\n");
	while (temp)
	{
		printf("value: %s\n", temp->value);
		printf("type: %d\n", temp->type);
		printf("quote type: %d\n", temp->quote_type);
		printf("link: %d\n\n", temp->link);
		temp = temp->next;
	}

	return (TRUE);
}

void	readline_loop(t_mshell *mshell)
{
	t_token 	*lexicon;
	t_parse		parsing;
	t_garbage	*g_collector;
	char		**envp;
	char		*prompt;

	while (1)
	{
		lexicon = NULL;
		g_collector = NULL;
		prompt = create_prompt(mshell->env);
		parsing.input = readline(prompt);
		add_to_garbage(&g_collector, NULL, (void *)parsing.input, FALSE);
		parsing.split_input = ft_split_charset(parsing.input, " ");
		add_to_garbage(&g_collector, (void **)parsing.split_input, NULL, TRUE);
		if (!parsing.split_input)
			break ;
		parsing.envp = envp;
		if (!parsing.input)
			break ;
		if (!parsing.input[0])
			continue ;
		add_history(parsing.input);
		mshell->args = parsing.split_input;
		if (create_lexicon(parsing.input, mshell, &lexicon) == FALSE)
			continue ;
		if (parsing_input(lexicon) == FALSE)
		{
			ft_putstr_fd("failed to parse\n", 2);
			continue ;
		}
		envp = convert_env_to_tab(mshell->env);
		exec(&lexicon, envp, mshell);
		cleanup_garbage(g_collector);
		free_lexicon(lexicon);
		lexicon = NULL;
	}
	cleanup_garbage(g_collector);
	free(prompt);
}

int	main(int argc, char **argv, char **envp)
{
	t_mshell	mshell;
	
	(void)argv;
	(void)argc;
	init_minishell(&mshell);
	env_creator(envp, &mshell);
	catch_sig();	
	readline_loop(&mshell);
	free_list(mshell.env);
	rl_clear_history();
	return (0);
}
