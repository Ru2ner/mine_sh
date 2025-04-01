/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:27:42 by tlutz             #+#    #+#             */
/*   Updated: 2025/04/01 17:47:46 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <readline/readline.h>
#include "libft.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)argc;
	char	*input;
	const char	*prompt = RED "minishell> " RESET;

	
	while (1)
	{
		input = readline(prompt);
		if (!input)
			break;
		if ((ft_strncmp(input, "env", 3) == 0) && (ft_strlen(input) == 3))
			print_env(envp);
		else if ((ft_strncmp(input, "pwd", 3) == 0) && (ft_strlen(input) == 3))
			fetch_cwd(envp);
		else
			ft_putendl_fd("Command not found", 1);
		free(input);
	}
	return (0);	
}
