# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/04 11:38:53 by prmerku           #+#    #+#              #
#    Updated: 2020/02/06 07:57:37 by prmerku          ###   ########.fr        #
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
# 							Flags and Lib name
# ----------------------------------------------------------------------------

CFLAGS = -Wall -Wextra -Werror -Ilibft -Imlx -Iinc

MLXFLAGS = -Lmlx/ -lmlx -framework OpenGL -framework AppKit

NAME = cub3D

# ----------------------------------------------------------------------------
# 							Objects and Includes
# ----------------------------------------------------------------------------

OBJ = main.o

OBJ += parser/parse_file.o parser/parse_info.o parser/parse_map.o \
	parser/parse_map_validate.o

OBJ += engine/renderer.o engine/movement.o engine/draw_back.o \
	engine/draw_utils.o engine/draw_walls.o engine/sprites.o

OBJ += utils/shutdown.o utils/data_handle.o

LIBFT = libft/libft.a

MLX = libmlx.dylib

# ----------------------------------------------------------------------------
# 							Rules
# ----------------------------------------------------------------------------

all: $(NAME)

f: $(MLX) $(LIBFT) $(OBJ)
	@printf "Compiling - ${YELLOW}[Fast build]${NC}\n"
	@$(CC) $(CFLAGS) $(MLXFLAGS) -o $(NAME) $^
	@printf "${MAGENTA}  Finished${NC}\n"

$(NAME): $(MLX) $(LIBFT) $(OBJ)
	@printf "Compiling - ${YELLOW}[Main build]${NC}\n"
	@$(CC) $(CFLAGS) $(MLXFLAGS) -o $@ $^
	@printf "${MAGENTA}  Finished${NC}\n"

$(LIBFT):
	@printf "Compiling - ${YELLOW}[Libft]${NC}\n"
	@$(MAKE) -C libft > /dev/null
	@printf "${MAGENTA}  Finished${NC}\n"

$(MLX):
	@printf "Compiling - ${YELLOW}[Mlx]${NC}\n"
	@$(MAKE) -C mlx > /dev/null
	@cp -r mlx/libmlx.dylib libmlx.dylib
	@printf "${MAGENTA}  Finished${NC}\n"

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@printf "Cleaning - ${YELLOW}[OBJ]${NC}\n"
	@$(MAKE) -C libft clean > /dev/null
	@$(MAKE) -C mlx clean > /dev/null
	@$(RM) $(OBJ)
	@printf "${MAGENTA}  Finished${NC}\n"

fclean: clean
	@printf "Cleaning - ${YELLOW}[NAME]${NC}\n"
	@$(MAKE) -C libft fclean > /dev/null
	@$(RM) mlx/libmlx.dylib libmlx.dylib > /dev/null
	@$(RM) $(NAME)
	@printf "${MAGENTA}  Finished${NC}\n"

re: fclean all

.PHONY: all clean fclean re