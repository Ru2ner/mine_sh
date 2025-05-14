/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_v1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:57:10 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/14 20:14:50 by tlutz            ###   ########.fr       */
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

t_bool	create_lexicon(char *input, t_parse *parsing, t_token **lexicon)
{
	
	if (quote_counter(input) == FALSE)
	{
		printf("There is an odd number of quotes\n");
		return (FALSE);
	}
	lexer(input, parsing, lexicon);
	t_token	*temp;
	temp = *lexicon;
	while (temp)
	{
		printf("%s\n", temp->value);
		printf("%d\n", temp->type);
		temp = temp->next;
	}
	return (TRUE);
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
		mshell->args = ft_split(parsing.input, ' ');
		if (create_lexicon(parsing.input, &parsing, &lexicon) == FALSE)
		continue ;
		if (parsing_input(lexicon) == FALSE)
		{
			ft_putstr_fd("failed to parse\n", 2);
			continue ;
		}
		exec(lexicon, envp, mshell); //TODO envoyer la conversion de la liste env en tableau
		free(parsing.input);
		free_tab(parsing.split_input);
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
	init_minishell(&mshell);
	env_creator(envp, &mshell);
	catch_sig();
	readline_loop(envp, &mshell);
	free_list(mshell.env);
	rl_clear_history();
	return (0);
}
