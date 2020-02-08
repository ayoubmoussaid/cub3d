# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/10 15:30:39 by amoussai          #+#    #+#              #
#    Updated: 2020/01/24 15:50:34 by amoussai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=cub3D
LIBFT=libft.a
MLX=libmlx.a
MANDATORY=./mandatory/
BONUSDIR=./bonus/
SRCS=$(MANDATORY)parsemap.c \
		$(MANDATORY)parsing1.c \
		$(MANDATORY)parsing2.c \
		$(MANDATORY)calculation.c \
		$(MANDATORY)drawing.c \
		$(MANDATORY)keys_handling.c \
		$(MANDATORY)move_arround.c \
		$(MANDATORY)game.c \
		$(MANDATORY)make_bmp.c\
		$(MANDATORY)ft_error.c

SRCSBONUS=$(MANDATORY)parsemap.c \
		$(MANDATORY)parsing1.c \
		$(MANDATORY)parsing2.c \
		$(BONUSDIR)calculation.c \
		$(BONUSDIR)drawing.c \
		$(BONUSDIR)keys_handling.c \
		$(BONUSDIR)move_arround.c \
		$(BONUSDIR)game.c \
		$(MANDATORY)make_bmp.c \
		$(BONUSDIR)extra_moves.c\
		$(MANDATORY)ft_error.c

OBJ=$(SRCS:.c=.o)
GNL=./gnl/get_next_line.c ./gnl/get_next_line_utils.c
FLAGS=-Wall -Werror -Wextra
CC=gcc
INCLUDE=raycaster.h
CFLAGS=$(GNL) libft.a libmlx.a -lz -framework OpenGL -framework AppKit
CFLAGSBONUS= -I ./sdl/SDL2.framework/Headers -I ./sdl/SDL2_mixer.framework/Headers -rpath @loader_path/SDL -framework SDL2 -F sdl/ -framework SDL2_mixer -F sdl/

.PHONY: clean bonus fclean all re

all: $(NAME)

$(NAME):
	$(MAKE) -C ./libft
	$(MAKE) -C ./minilibx
	mv ./minilibx/$(MLX) .
	mv ./libft/$(LIBFT) .
	$(CC) $(FLAGS) $(SRCS) $(CFLAGS) -o $(NAME)

bonus:
	$(MAKE) -C ./libft
	$(MAKE) -C ./minilibx
	mv ./minilibx/$(MLX) .
	mv ./libft/$(LIBFT) .
	$(CC) $(FLAGS) $(SRCSBONUS) $(CFLAGS) $(CFLAGSBONUS) -o $(NAME)
clean:
	$(MAKE) -C ./libft clean
	$(MAKE) -C ./minilibx clean
fclean: clean
	$(MAKE) -C ./libft fclean
	rm -f $(NAME)
	rm -f $(LIBFT)
	rm -f $(MLX)
re: fclean all
