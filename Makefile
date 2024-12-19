# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svereten <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/05 16:02:29 by svereten          #+#    #+#              #
#    Updated: 2024/12/19 13:32:31 by jwolfram         ###   ########.fr        #
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

LIBFT_DIR = libft
SRC_DIR = src
OBJ_DIR = obj

FILES = main \
		data \
		env \
		path \
		loop \
		signal \
		lexer \
		parser \
		utils/exit \
		utils/ischar \
		utils/words \
		utils/minishell_split \
		dev 
		# -> dev file, delete later #
		
SRCS = ${FILES:%=${SRC_DIR}/%.c}
OBJS = ${FILES:%=${OBJ_DIR}/%.o}

OBJ_DIRS = ${sort ${dir ${OBJS}}}

###############################################################################
#
# Dev vars
# 
###############################################################################

INCLUDE_FILES = ${wildcard include/*.h}

CFLAGS := ${CFLAGS} -g

DEV_FILES =	${wildcard src/dev*.c} 

###############################################################################
#
# Project targets
# 
###############################################################################

all: ${NAME}

${NAME}: ${OBJS} | ${LIBFT}
	${CC} ${CFLAGS} ${INCLUDE} ${OBJS} -o $@ ${LDLIBS} ${LDFLAGS}

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c | ${OBJ_DIRS}
	${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@

${LIBFT}:
	${MAKE} -C ${LIBFT_DIR} GNL_SIZE="-D BUFFER_SIZE=42"

${OBJ_DIRS}:
	mkdir -p $@

clean:
	rm -rf ${OBJ_DIR}
	${MAKE} clean -C ${LIBFT_DIR}

fclean: clean
	rm -rf ${NAME}
	${MAKE} fclean -C ${LIBFT_DIR}

re: fclean all

###############################################################################
#
# Dev targets
# 
###############################################################################

run: re
	./minishell

print:
	echo ${INCLUDE_FILES} ${DEV_FILES}

norm:
	norminette ${SRCS} ${INCLUDE_FILES}

.PHONY: all clean fclean re norm
