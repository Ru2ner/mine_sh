/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list_creator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarion <tmarion@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:08:09 by tlutz             #+#    #+#             */
/*   Updated: 2025/06/05 14:46:10 by tmarion          ###   ########.fr       */
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

static int	count_fd(int in_out, t_token *lexicon)
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
		if (temp->type == INFILE && in_out == 0)
			count++;
		if (temp->type == OUTFILE && in_out == 1)
			count++;
		temp = temp->next;
	}
	return (count);
}

static char	**stock_fd(int in_out, t_token *lexicon)
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
		if (in_out == 1 && (temp->type == OUTFILE \
			|| temp->type == OUTFILE_APPEND))
		{
			tab[i] = ft_strdup((char *)temp->value);
			i++;
		}
		temp = temp->next;
	}
	tab[i] = NULL;
	return (tab);
}

static t_bool	parse_fd(char ***g_tab)
{
	int	i;
	int	fd;

	i = 0;
	while (g_tab[1][i])
	{
		fd = open((const char *)g_tab[1][i], O_RDONLY);
		if (fd == -1)
		{
			fd = open((const char *)g_tab[1][i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			i++;
		}
		else
			i++;
		close(fd);
	}
	i = 0;
	while (g_tab[0][i])
	{
		fd = open((const char *)g_tab[0][i], O_RDONLY);
		if (fd == -1)
			return (FALSE);
		else
		{
			close(fd);
			i++;
		}
	}
	return (TRUE);
}

int	exec(t_token **lexicon, t_mshell *mshell)
{
	t_cmd	*cmd_list;
	char	***giga_tab;
	t_token	*tmp;

	cmd_list = NULL;
	tmp = *lexicon;
	giga_tab = malloc(sizeof(char **) * 3);
	if (!giga_tab)
		return (0);
	giga_tab[1] = stock_fd(1, *lexicon);//fd_out
	giga_tab[0] = stock_fd(0, *lexicon);//fd_in
	giga_tab[2] = NULL;
	if (parse_fd(giga_tab) == FALSE)
	{
		free_tab(giga_tab[0]);
		free_tab(giga_tab[1]);
		free(giga_tab);
		free_lexicon(tmp);
		free_tab(mshell->env_tab);
		free_cmd_list(cmd_list);
		printf("\n\nfailed to open:infile\n\n");
		return (0);
	}
	free_tab(giga_tab[0]);
	free_tab(giga_tab[1]);
	free(giga_tab);
	create_exec_list(&cmd_list, lexicon, mshell->env);
	if (DEBUG == 1)
		print_exec_list(cmd_list);
	free_lexicon(tmp);
	pipeline(cmd_list, mshell);
	free_tab(mshell->env_tab);
	free_cmd_list(cmd_list);
	return (1);
}
