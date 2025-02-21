# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svereten <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/05 16:02:29 by svereten          #+#    #+#              #
#    Updated: 2025/02/21 13:24:03 by svereten         ###   ########.fr        #
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
LIBFT_DEFINES = GNL_SIZE="-D BUFFER_SIZE=42" PANIC_MSG=minishell DEBUG=1

LIBFT_DIR = libft
SRC_DIR = src
OBJ_DIR = obj

FILES = main \
		data \
		env_init \
		env_update \
		path \
		loop \
		signal \
		lexer \
		lexer_redir \
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
		utils/substrrplc \
		utils/ft_getenv \
		utils/valid_operator \
		utils/heredoc_var \
		utils/minishell_split \
		utils/str_has_quotes \
		utils/str_isspace \
		dev 
		# -> dev file, delete later #
		
SRCS = ${FILES:%=${SRC_DIR}/%.c}
OBJS = ${FILES:%=${OBJ_DIR}/%.o}

OBJ_DIRS = ${sort ${dir ${OBJS}}}

DEFAULT = \033[0m

BLUE = \033[1;34m

GREEN = \033[1;32m

###############################################################################
#
# Dev vars
# 
###############################################################################


INCLUDE_FILES = ${wildcard include/*.h}

CFLAGS := ${CFLAGS} -g

OBJS := ${OBJS} ${DEV_FILES:%=${OBJ_DIR}/%.o}

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

###############################################################################
#
# Dev targets
# 
###############################################################################

test: re
	bash ${HOME}/42_minishell_tester/tester.sh m

noenv: CFLAGS += -D DEBUG=1
noenv: re
	@clear
	@env -i ./minishell

run: CFLAGS += -D DEBUG=1
run: re
	@clear
	@./minishell

release: re
	@clear
	@./minishell

print:
	echo ${INCLUDE_FILES} ${DEV_FILES}

norm:
	norminette ${SRCS} ${INCLUDE_FILES}

.PHONY: all clean fclean re norm
