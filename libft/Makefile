# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svereten <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/09 14:07:03 by svereten          #+#    #+#              #
#    Updated: 2025/01/11 16:37:46 by svereten         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

ifdef DEBUG
	CFLAGS := ${CFLAGS} -g
endif

SRCS_DIR = src

OBJS_DIR = obj

SRCS_PROJ = libft/ft_toupper \
			libft/ft_tolower \
			libft/ft_lstnew \
			libft/ft_lstadd_front \
			libft/ft_lstadd_back \
			libft/ft_lstsize \
			libft/ft_lstlast \
			libft/ft_lstdelone \
			libft/ft_lstclear \
			libft/ft_lstiter \
			libft/ft_lstmap \
			ctype/ft_isalpha \
			ctype/ft_isascii \
			ctype/ft_isdigit \
			ctype/ft_isprint \
			ctype/ft_isnumber \
			ctype/ft_isalnum \
			ctype/ft_isspace \
			string/ft_strlen \
			string/ft_memset \
			string/ft_bzero \
			string/ft_memcpy \
			string/ft_memmove \
			string/ft_memchr \
			string/ft_memcmp \
			string/ft_strchr \
			string/ft_strrchr \
			string/ft_strncmp \
			string/ft_strcmp \
			string/ft_strlcpy \
			string/ft_strlcat \
			string/ft_strnstr \
			string/ft_strdup \
			string/ft_substr \
			string/ft_substri \
			string/ft_strjoin \
			string/ft_strtrim \
			string/ft_count_words \
			string/ft_split \
			string/ft_strmapi \
			string/ft_striteri \
			stdlib/ft_atoi \
			stdlib/ft_atoi_check \
			stdlib/ft_itoa \
			stdlib/ft_calloc \
			stdlib/ft_free \
			stdlib/ft_panic \
			stdlib/ft_exit \
			stdio/ft_putchar_fd \
			stdio/ft_putstr_fd \
			stdio/ft_putstrarr_fd \
			stdio/ft_putendl_fd \
			stdio/ft_putnbr_fd \
			stdio/ft_putuint_fd \
			stdio/ft_putuhex_fd \
			stdio/ft_printf \
			strarr/ft_strarrdup \
			strarr/ft_strarrlen \
			strarr/ft_strarrcmp \
			unistd/ft_open \
			unistd/ft_close \
			gnl/get_next_line \
			internal/gc/gc \
			internal/gc/gc_data \
			internal/ft_calloc_no_gc \
			internal/libft_init \
			internal/ft_putaddr_fd \

OBJS = ${SRCS_PROJ:%=${OBJS_DIR}/%.o}

INCLUDES = -I./include -I./internal

AR = ar -rcs

RM = rm -rf

OBJS_DIRS = ${sort ${dir ${OBJS}}} obj/gnl

GNL_SIZE ?= -D BUFFER_SIZE=42

PANIC_MSG ?= libft

all: ${NAME}

${NAME}: ${OBJS}
	${AR} ${NAME} $^

# Special compilation

obj/gnl/get_next_line.o: src/gnl/get_next_line.c | ${OBJS_DIRS}
	${CC} ${CFLAGS} ${GNL_SIZE} -c $< ${INCLUDES} -o $@
	
obj/stdlib/ft_panic.o: src/stdlib/ft_panic.c | ${OBJS_DIRS}
	${CC} ${CFLAGS} -D PANIC_MSG=\"${PANIC_MSG}\" -c $< ${INCLUDES} -o $@

# Generic compilation

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c | ${OBJS_DIRS}
	${CC} ${CFLAGS} -c $< ${INCLUDES} -o $@ 

${OBJS_DIRS}:
	mkdir -p $@

clean:
	${RM} ${OBJS_DIR}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all bonus clean fclean re
