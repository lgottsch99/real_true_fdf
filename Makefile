# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgottsch <lgottsch@student.42prague.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/18 16:00:38 by lgottsch          #+#    #+#              #
#    Updated: 2024/12/07 19:56:52 by lgottsch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#TO DO 
#default make => linux
#make rule for mac
#.a or .dylib files need lib- prefix for linker at compilation

NAME = fdf

LIBFTDIR= ./full_libft
MLXDIR= ./mlx_linux

CC = cc 
CFLAGS = -Wall -Wextra -Werror

MLX_FLAGS_LX = -I/usr/X11/include -L/usr/X11/lib -lX11 -lXext -lm -g
MLX_FLAGS_MAC = -Lmlx_mac -lmlx -Lfull_libft -lfull_libft -framework OpenGL -framework AppKit

SRC= fdf.c color.c gradient.c hooks.c parse_map.c create_image.c utils.c draw_lines.c free.c free_extra.c bresenham_extra.c
OBJ = $(SRC:.c=.o)

LIBFTA= full_libft/libfull_libft.a
MLXA= mlx_linux/libmlx_Linux.a
		

$(NAME): libft mlx-linux
	$(CC) $(CFLAGS) $(SRC) $(LIBFTA) $(MLXA) -o $(NAME) $(MLX_FLAGS_LX)

libft:
	@make -C full_libft

mlx-linux: 
	cd mlx_linux && ./configure

all: $(NAME)

clean:
	rm -f $(OBJ)
	@cd $(LIBFTDIR) && make clean
	@cd $(MLXDIR) && make clean

fclean: clean
	rm -f $(NAME)
	@cd $(LIBFTDIR) && make clean
	@cd $(MLXDIR) && make clean

re: fclean all

norm:
	norminette $(SRC) $(LIBFTDIR)

#compilation on mac
mac: libft 
	cd mlx_mac && make
	cd ..
	$(CC) $(CFLAGS) $(SRC) $(LIBFTA) -o $(NAME) $(MLX_FLAGS_MAC)
	mv ./mlx_mac/libmlx.dylib ./

.PHONY: all clean fclean re libft mlx-linux mac norm