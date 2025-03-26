/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:00:25 by tlutz             #+#    #+#             */
/*   Updated: 2025/03/26 16:20:37 by tlutz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	TOKEN_HERE_DOC,
}	t_token_type;

typedef struct s_token
{
	t_token_type type;
	char	*value;
	t_token	*next;
}	t_token;

typedef struct s_cmd
{
	char	*name;
	char	**args;
	//redirection si besoin
	t_cmd	*next;
}	t_cmd;

/****************************Error Handling************************************/




/******************************Tokenizer***************************************/




/******************************Args Checks*************************************/



#endif