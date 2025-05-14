/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigs_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:13:11 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/14 14:51:07 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "exec.h"
#include <readline/readline.h>

void	sigint_handler(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	catch_sig(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}

void	here_doc_sigint_handler(int signum)
{
	(void)signum;
	printf("\n");
	exit(130);
}

void	catch_sig_heredoc(void)
{
	struct sigaction	sa_heredoc;
	
	sa_heredoc.sa_handler = here_doc_sigint_handler;
	sa_heredoc.sa_flags = 0;
	sigemptyset(&sa_heredoc.sa_mask);
	sigaction(SIGINT, &sa_heredoc, NULL);
}
