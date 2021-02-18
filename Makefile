# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/04 11:38:53 by prmerku           #+#    #+#              #
#    Updated: 2020/02/17 14:31:38 by prmerku          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ----------------------------------------------------------------------------
# 							Colors
# ----------------------------------------------------------------------------

OS      :=  $(shell uname -s)
CC      =   clang
WFLAGS  =   -Wall -Wextra -Werror
EFLAGS  =
GDBFLAG =
SDIR    =   .
ODIR    =   .
IDIR    =   -Iinclude -Ilibft/include
LIBFT   =   -Llibft/build -lft
DEFINE  =   -D LINUX_CUBE
NAME    =   cub3D

# ----------------------------------------------------------------------------
# 							Objects and Includes
# ----------------------------------------------------------------------------

FNAME   =   main.c parser/parse_file.c parser/parse_info.c parser/parse_sprites.c \
	parser/parse_map.c parser/parse_map_validate.c parser/parse_color.c \
	engine/renderer.c engine/movement.c engine/rotation.c engine/draw_back.c \
	engine/engine_utils.c engine/draw_walls.c engine/draw_sprites.c \
	engine/sprite_utils.c \
	utils/shutdown.c utils/data_handle.c utils/bitmap.c utils/bitmap_utils.c \
	utils/hud.c

SRC     =   $(FNAME:%.c=$(SDIR)/%.c)
OBJ     =   $(SRC:$(SDIR)/%.c=$(ODIR)/%.o)
ifeq ($(OS),Darwin)
    MLX     =   -Lmlx -lmlx -framework OpenGL -framework AppKit
    DEFINE  =   -D MAC_AND_CHEESE_CUBE
    IDIR    +=  -Imlx
    CMLX    =   mlx
else
    MLX     =   -Lmlx_linux -lmlx -lXext -lX11 -lz -lm
    IDIR    +=  -Imlx_linux
    CMLX    =   mlx_linux
endif
ifdef WITH_DEBUG
    FLAGS = $(GDBFLAG) $(WFLAGS) $(EFLAGS)
    DBG = WITH_DEBUG=1
else
    FLAGS = $(WFLAGS)
endif
all         : libft mlx $(NAME)
$(NAME)     : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(IDIR) $(LIBFT) $(MLX) -o $(NAME) $(DEFINE)
bonus		:
	@$(MAKE) WITH_BONUS=1 all
debug       :
	@$(MAKE) WITH_BONUS=1 WITH_DEBUG=1 all
rebug       : fclean debug
clean       :
	/bin/rm -f $(OBJ)
	$(MAKE) -C $(CMLX) clean
fclean      : clean
	/bin/rm -f $(NAME)
	/bin/rm -f mlx/libmlx.dylib libmlx.dylib
re          :
	$(MAKE) fclean
	$(MAKE) all
libft       :
	cd libft; cmake . && make
mlx         :
	$(MAKE) -C $(CMLX) $(DBG)
ifeq ($(OS),Darwin)
	cp mlx/libmlx.dylib .
endif
$(ODIR)/%.o : $(SDIR)/%.c
	$(CC) -c $(FLAGS) $< $(IDIR) -o $@ $(DEFINE)
.PHONY      : all bonus clean fclean re debug rebug libft mlx
