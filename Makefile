# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/26 16:56:56 by tlutz             #+#    #+#              #
#    Updated: 2025/03/26 16:57:17 by tlutz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

INCFLAG = -I
CFLAGS = -Wall -Werror -Wextra -g3
CC = cc

HEADERSDIR = includes/

HEADERS =

SRCSDIR = srcs/
SRCS = 

OBJSDIR = build/

OBJS = $(patsubst %.c, $(OBJSDIR)%.o,$(SRCS))

.PHONY : all
all : $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

$(OBJSDIR)%.o : $(SRCSDIR)%.c $(HEADERS) | $(OBJSDIR)
		$(CC) -o $@ -c $< $(CFLAGS) $(INCFLAG)$(HEADERSDIR)

$(OBJSDIR) :
		@mkdir -p $(OBJSDIR)

.PHONY : clean
clean : 
		rm -rf $(OBJSDIR)

.PHONY : fclean
fclean : clean
		rm -f $(NAME)

.PHONY : re
re : fclean all