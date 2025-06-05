# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlutz <tlutz@student.42lyon.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/02 18:30:28 by tlutz             #+#    #+#              #
#    Updated: 2025/06/05 19:36:12 by tlutz            ###   ########.fr        #
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
DEBUG_CFLAGS = -Wall -Werror -Wextra -g3 -DDEBUG=1

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
		lexer/lexer_utils/type_finder.c \
		lexer/lexer_utils/path_access.c \
		lexer/lexer_utils/list_utils.c \
		lexer/extractors.c \
		lexer/lexer.c \
		lexer/lexer_helpers.c \
		parser/parse_utils.c\
		builtins/builtin_pwd.c \
		builtins/builtin_exit.c \
		builtins/builtin_env.c \
		builtins/builtin_cd.c \
		builtins/builtin_echo.c \
		builtins/builtin_clear.c \
		builtins/builtin_export.c \
		builtins/builtin_unset.c \
		builtins/builtin_launcher.c \
		expand_handler/expand_handler.c \
		expand_handler/expand_utils.c \
		env_handling/env_converter.c \
		env_handling/env_editor.c \
		env_handling/env_list_utils.c \
		env_handling/env_creator.c \
		builtins_utils/free_utils.c \
		builtins_utils/tab_utils.c \
		builtins_utils/cd_utils.c \
		builtins_utils/print_export_utils.c \
		builtins_utils/export_utils.c \
		errors_handling/errors_msgs.c \
		cleanup/cleanup_utils.c \
		exec/exec_list_creator.c \
		exec/exec_list_utils.c \
		exec_part/exec.c \
		exec_part/exec_utils.c \
		exec_part/cmd_finder.c \
		signals/sigs_handlers.c \
		prompt/create_prompt.c \
		garbage_collector/garbage_collector.c \
		debug/debug_print_helpers.c \
		exec_part/child_waiting.c \
		errors_handling/exec_error_msgs.c \
		exec_part/exec_helpers.c \
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

.PHONY : debug
debug : CFLAGS = $(DEBUG_CFLAGS)
debug : fclean $(NAME)
	@echo "$(COLOR_PURPLE)$(NAME) successfully compiled in debug mode !$(COLOR_RESET)"

.PHONY : val
val : $(NAME)
	valgrind --log-socket=127.0.0.1 --leak-check=full --trace-children=yes --suppressions=readline.supp --track-fds=yes --show-leak-kinds=all --track-origins=yes ./$(NAME)


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