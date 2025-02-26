# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/25 17:01:18 by jwolfram          #+#    #+#              #
#    Updated: 2025/02/25 17:01:22 by jwolfram         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###############################################################################
#
# Project vars
# 
###############################################################################
NAME = minishell

CC = cc

CFLAGS = -Wall -Werror -Wextra

INCLUDE = -I./include -I./libft/include

LDLIBS = -lft -lreadline
LDFLAGS = -L./libft

LIBFT = libft/libft.a
LIBFT_DEFINES = GNL_SIZE="-D BUFFER_SIZE=42" PANIC_MSG=minishell

LIBFT_DIR = libft
SRC_DIR = src
OBJ_DIR = obj

FILES = main \
		data \
		path \
		loop \
		signal \
		lexer \
		lexer_redir \
		env/env_init \
		env/env_to_arr \
		env/env_utils \
		executor/executor \
		executor/commands \
		executor/cmd \
		executor/child/child \
		executor/child/execute \
		executor/child/kill \
		executor/heredoc \
		parser/parser \
		parser/prompt \
		parser/token \
		parser/expander \
		parser/quotes_rm \
		parser/command_table \
		parser/command_table_redir \
		parser/command_table_arr \
		builtins/exit \
		builtins/cd \
		builtins/env \
		builtins/unset \
		builtins/pwd \
		builtins/export/export \
		builtins/export/no_args \
		builtins/echo \
		utils/exit \
		utils/redirect \
		utils/stdfd \
		utils/pipe_close \
		utils/words \
		utils/ischar \
		utils/is_builtin \
		utils/is_directory \
		utils/is_first_word \
		utils/substrrplc \
		utils/ft_getenv \
		utils/valid_operator \
		utils/heredoc_var \
		utils/minishell_split \
		utils/str_has_quotes \
		utils/str_isspace \
		
SRCS = ${FILES:%=${SRC_DIR}/%.c}
OBJS = ${FILES:%=${OBJ_DIR}/%.o}

OBJ_DIRS = ${sort ${dir ${OBJS}}}

DEFAULT = \033[0m

BLUE = \033[1;34m

GREEN = \033[1;32m

###############################################################################
#
# Project targets
# 
###############################################################################

all: ${NAME}

${NAME}: ${OBJS} | ${LIBFT}
	@${CC} ${CFLAGS} ${INCLUDE} ${OBJS} -o $@ ${LDLIBS} ${LDFLAGS}
	@echo "${GREEN}--------------------------${DEFAULT}"
	@echo "${GREEN}   COMPILATION COMPLETE   ${DEFAULT}"
	@echo "${GREEN}--------------------------${DEFAULT}"

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c | ${OBJ_DIRS}
	@${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@

${LIBFT}:
	@${MAKE} -C ${LIBFT_DIR} ${LIBFT_DEFINES}

${OBJ_DIRS}:
	@mkdir -p $@

clean:
	@rm -rf ${OBJ_DIR}
	@${MAKE} clean -C ${LIBFT_DIR}
	@echo "${BLUE}--------------------------${DEFAULT}"
	@echo "${BLUE}     CLEANUP COMPLETE     ${DEFAULT}"
	@echo "${BLUE}--------------------------${DEFAULT}"

fclean: clean
	@rm -rf ${NAME}
	@${MAKE} fclean -C ${LIBFT_DIR}

re: fclean all

.PHONY: all clean fclean re
