# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/02 18:30:28 by tlutz             #+#    #+#              #
#    Updated: 2025/05/20 14:36:59 by tlutz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COLOR_GREEN = \033[0;32m
COLOR_RED = \033[0;31m
COLOR_YELLOW = \033[0;33m
COLOR_BLUE = \033[0;34m
COLOR_PURPLE = \033[0;35m
COLOR_CYAN = \033[0;36m
COLOR_RESET = \033[0m

NAME = minishell

INCFLAG = -I
LINKREADLINE = -lreadline
CFLAGS = -Wall -Werror -Wextra -g3
CC = cc

LIBFTDIR = 42Libft/
LIBFTINCDIR = $(LIBFTDIR)includes/
LIBFTHEADER = $(LIBFTINCDIR)libft.h \
				$(LIBFTINCDIR)get_next_line.h
LIBFT = $(LIBFTDIR)libft.a

HEADERSDIR = includes/

HEADERS = $(HEADERSDIR)parsing.h \
			$(HEADERSDIR)exec.h \
			$(HEADERSDIR)errors.h \
			$(HEADERSDIR)env_handling.h \
			$(HEADERSDIR)structs.h

SRCSDIR = srcs/
SRCS = lexer/lexer_utils/quote_checker.c \
		lexer/lexer_utils/token_checker_utils.c \
		lexer/lexer_utils/is_type.c \
		lexer/lexer_utils/path_access.c \
		lexer/lexer_utils/list_utils.c \
		lexer/extractors.c \
		lexer/lexer_rework/lexer.c \
		parser/parse_utils.c\
		builtins/builtin_pwd.c \
		builtins/builtin_env.c \
		builtins/builtin_cd.c \
		builtins/builtin_echo.c \
		builtins/builtin_clear.c \
		builtins/builtin_export.c \
		builtins/builtin_unset.c \
		builtins/builtin_launcher.c \
		expand_handler/expand_handler.c \
		env_handling/env_converter.c \
		env_handling/env_editor.c \
		env_handling/env_list_utils.c \
		env_handling/env_creator.c \
		builtins_utils/free_utils.c \
		builtins_utils/tab_utils.c \
		builtins_utils/export_utils.c \
		errors_handling/errors_msgs.c \
		pipex_exec/pipex_bonus.c \
		pipex_exec/pipex_utils_bonus_1.c \
		pipex_exec/pipex_utils_bonus_2.c \
		pipex_exec/pipex_utils_bonus.c \
		exec/exec_creator.c \
		exec_part/exec.c \
		exec_part/exec_utils.c \
		exec_part/cmd_finder.c \
		signals/sigs_handlers.c \
		prompt/create_prompt.c \
		main_v1.c

OBJSDIR = .build/

OBJS = $(patsubst %.c, $(OBJSDIR)%.o,$(SRCS))

TOTAL_SRCS := $(words $(SRCS))
COMPILED_SRCS := 0

.PHONY : all
all : $(NAME)

$(NAME) : $(OBJS) | $(LIBFT)
	@echo "\n$(COLOR_GREEN)Linking objects...$(COLOR_RESET)"
	@$(CC) $(OBJS) $(LIBFT) $(CFLAGS) $(LINKREADLINE) -o $(NAME)
	@echo "$(COLOR_RED)$(NAME) compiled !$(COLOR_RESET)"

$(OBJSDIR)%.o : $(SRCSDIR)%.c $(HEADERS) | $(OBJSDIR) $(LIBFT)
	@mkdir -p $(dir $@)
	@$(eval COMPILED_SRCS=$(shell echo $$(($(COMPILED_SRCS)+1))))
	@printf "\rCompiling $(NAME): [%-50s] %d/%d" \
	"$(shell printf '#%.0s' $$(seq 1 $$(($(COMPILED_SRCS)*50/$(TOTAL_SRCS)))))" \
	$(COMPILED_SRCS) $(TOTAL_SRCS)
	@$(CC) -o $@ -c $< $(CFLAGS) $(INCFLAG)$(HEADERSDIR) $(INCFLAG)$(LIBFTINCDIR)

$(OBJSDIR) :
	@mkdir -p $(OBJSDIR)

$(LIBFT) :
	@make -j -sC $(LIBFTDIR)

.PHONY : clean
clean :
	@echo "$(COLOR_BLUE)Cleaning objects...$(COLOR_RESET)"
	@rm -rf $(OBJSDIR)
	@make clean -sC $(LIBFTDIR)

.PHONY : fclean
fclean : clean
	@echo "$(COLOR_CYAN)Cleaning executable...$(COLOR_RESET)"
	@rm -f $(NAME)
	@make fclean -sC $(LIBFTDIR)

.PHONY : re
re : fclean all