/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list_creator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:08:09 by tlutz             #+#    #+#             */
/*   Updated: 2025/05/27 13:54:30 by tmarion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parsing.h"
#include "libft.h"
#include <signal.h>

static void	create_exec_list(t_cmd **cmd_list, t_token **lexicon, t_env *env)
{
	t_cmd	*new_node;
	t_cmd	*tail;

	while (*lexicon)
	{
		new_node = ft_create_node(lexicon, env);
		if (!new_node)
			return ;
		if (!*cmd_list)
			*cmd_list = new_node;
		else
			tail->next = new_node;
		tail = new_node;
		while (*lexicon && (*lexicon)->type != PIPE)
			*lexicon = (*lexicon)->next;
		if (*lexicon && (*lexicon)->type == PIPE)
			*lexicon = (*lexicon)->next;
	}
}

static int count_fd(int in_out, t_token *lexicon)
{
	t_token	*temp;
	size_t	count;

	temp = lexicon;
	if (!lexicon || !temp)
		return (0);
	count = 0;
	if (!lexicon || (in_out != 1 && in_out != 0))
		return (0);
	while (temp)
	{
		if ( temp->type == INFILE && in_out == 0)
			count++;
		if ( temp->type == OUTFILE && in_out == 1)
			count++;
		temp = temp->next;
	}
	return (count);
}

static char **stock_fd(int in_out, t_token *lexicon)
{
	t_token	*temp;
	char	**tab;
	int		fd_nb;
	int		i;

	i = 0;
	fd_nb = count_fd(in_out, lexicon);
	tab = (char **)malloc(sizeof(char *) * (fd_nb + 1));
	if (!tab)
		return (NULL);
	i = 0;
	temp = lexicon;
	while (temp && i <= fd_nb)
	{
		if (in_out == 0 && (temp->type == INFILE))
		{
			tab[i] = ft_strdup((char *)temp->value);
			i++;
		}
		if (in_out == 1 && (temp->type == OUTFILE || temp->type == OUTFILE_APPEND))
		{
			tab[i] = ft_strdup((char *)temp->value);
			i++;
		}
		temp = temp->next;
	}
	tab[i] = NULL;
	return (tab);
}

static t_bool parse_fd(char ***g_tab)
{
	int	i;

	i = 0;
	while (g_tab[0][i])
	{
		if (open((const char *)g_tab[0][i], O_RDONLY) == -1)
			return (FALSE);
		else
			i++;
	}
	i = 0;
	while (g_tab[1][i])
	{
		if (open((const char *)g_tab[1][i], O_RDONLY) == -1)
		{
			open((const char *)g_tab[1][i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			i++;
		}
		else
			i++;
	}
	return (TRUE);
}

int exec(t_token **lexicon, char **envp, t_mshell *mshell)
{
	t_cmd	*cmd_list = NULL;
	char	***giga_tab;
	
	giga_tab = malloc(sizeof(char **) * 3);
	if (!giga_tab)
		return (0);
	giga_tab[2] = NULL;
	giga_tab[0] = stock_fd(0, *lexicon);//fd_in
	giga_tab[1] = stock_fd(1, *lexicon);//fd_out
	if (parse_fd(giga_tab) == FALSE)
	{
		printf("\n\nfailed to open:infile\n\n");
		return (0);
	}
	free_tab(giga_tab[0]);
	free_tab(giga_tab[1]);
	free(giga_tab);
	create_exec_list(&cmd_list, lexicon, mshell->env);
	//
		// int		i;
		// printf("------------------Exec List--------------------------------------\n");
		// t_cmd	*temp;
		// temp = cmd_list;
		// i = 0;
		// while (temp)
		// {
		// 	i = 0;
		// 	if (temp->args != NULL)
		// 	{
		// 		while (temp->args[i])
		// 		{
		// 			printf("args: %s \n", temp->args[i]);
		// 			i++;
		// 		}
		// 	}
		// 	printf("infile: %s \n outfile: %s \n append: %d \n pipe: %d \n heredoc: %s \n", temp->infile, temp->outfile, temp->append, temp->pipe, temp->heredoc_delim);
		// 	temp = temp->next;
		// }
	//
	pipeline(cmd_list, envp, mshell, *lexicon);
	free_cmd_list(cmd_list);
	return (1);
}
