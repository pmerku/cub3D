# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/07 17:55:28 by prmerku           #+#    #+#              #
#    Updated: 2019/12/10 08:30:24 by prmerku       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# ----------------------------------------------------------------------------
# 							Colors
# ----------------------------------------------------------------------------

GREEN = \033[0;32m
RED = \033[0;31m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
YELLOW = \033[1;33m
NC = \033[0m

# ----------------------------------------------------------------------------
# 							Flags and lib name
# ----------------------------------------------------------------------------
CC = clang

CFLAGS = -Wall -Wextra -Werror -Ofast

NAME = libft.a

# ----------------------------------------------------------------------------
# 							Objects
# ----------------------------------------------------------------------------

OBJ =	ft_bzero.o ft_calloc.o ft_memccpy.o ft_memchr.o ft_memcmp.o \
		ft_memcpy.o ft_memmove.o ft_memset.o \
		ft_split.o ft_strchr.o ft_strdup.o ft_strjoin.o ft_strlcat.o \
		ft_strlcpy.o ft_strlen.o ft_strmapi.o ft_strncmp.o ft_strnlen.o \
		ft_strnstr.o ft_strrchr.o ft_strtrim.o ft_substr.o \
		ft_atoi.o ft_itoa.o ft_itoa_base.o \
		ft_isalnum.o ft_isalpha.o ft_isascii.o ft_isdigit.o ft_isprint.o \
		ft_tolower.o ft_toupper.o \
		ft_putchar_fd.o ft_putendl_fd.o ft_putnbr_fd.o ft_putstr_fd.o \
		ft_lstadd_back.o ft_lstadd_front.o ft_lstclear.o ft_lstdelone.o \
		ft_lstiter.o ft_lstlast.o ft_lstmap.o ft_lstnew.o ft_lstsize.o \
		get_next_line.o

# ----------------------------------------------------------------------------
# 							Rules
# ----------------------------------------------------------------------------

all: $(NAME)

$(NAME): $(OBJ)
	@printf "Compiling - ${YELLOW}[Libft]${NC}\n"
	@ar rcs $(NAME) $(OBJ)
	@printf "${MAGENTA}  Finished${NC}\n"

%.o: %.c
	@printf "Compiling - ${RED}$<${NC}\n"
	@$(CC) $(CFLAGS) -I. -c $<

clean:
	@printf "Clean ${YELLOW}[OBJ]${NC}\n"
	@/bin/rm -f $(OBJ)
	@printf "${MAGENTA}  Finished${NC}\n"

fclean: clean
	@printf "Clean ${YELLOW}[NAME]${NC}\n"
	@/bin/rm -f $(NAME)
	@printf "${MAGENTA}  Finished${NC}\n"

re: fclean all

.PHONY: clean fclean re
