/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:27:42 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/02 19:02:24 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)argc;
	char	*input;
	const char	*prompt = RED "minishell> " RESET;
	char	**args;
	t_env	*env = NULL;

	convert_env_to_list(envp, &env);
	while (1)
	{
		input = readline(prompt);
		if (!input)
			break;
		add_history(input);
		args = ft_split(input, ' ');
		if ((ft_strncmp(input, "env", 3) == 0) && (ft_strlen(input) == 3))
			print_env(envp);
		else if ((ft_strncmp(input, "pwd", 3) == 0) && (ft_strlen(input) == 3))
			fetch_cwd(env);
		// else if ((ft_strncmp(input, "cd", 2) == 0))
		// 	execute_cd(args[1]);
		else
			ft_putendl_fd("Command not found", 1);
		free(input);
		free_tab(args);
	}
	free_list(env);
	return (0);	
}
