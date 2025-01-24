# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svereten <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/05 16:02:29 by svereten          #+#    #+#              #
#    Updated: 2025/01/24 18:41:49 by svereten         ###   ########.fr        #
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
		executor/executor \
		executor/commands \
		executor/cmd \
		executor/child/child \
		executor/child/execute \
		executor/child/kill \
		executor/heredoc \
		utils/exit \
		utils/redirect \
		utils/stdfd \
		utils/pipe_close \
		parser/parser \
		parser/prompt \
		parser/token \
		parser/expander \
		parser/quotes_rm \
		builtins/exit \
		utils/words \
		utils/ischar \
		utils/substrrplc \
		utils/ft_getenv \
		utils/valid_operator \
		utils/minishell_split \
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

DEV_FILES = executor/dev \

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

run: re
	@clear
	@./minishell

print:
	echo ${INCLUDE_FILES} ${DEV_FILES}

norm:
	norminette ${SRCS} ${INCLUDE_FILES}

.PHONY: all clean fclean re norm
