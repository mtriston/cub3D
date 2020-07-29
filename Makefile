NAME = cub3D
CC = gcc
CFLAGS = -Wall -Werror -Wextra 

MLX_DIR = ./minilibx-linux
MLX_FLAGS = -L $(MLX_DIR) -lmlx -L /usr/include/../lib -lXext -lX11 -lm -lbsd 
LIBFT = ./ft_printf/libftprintf.a
LIBFT_DIR = ./ft_printf
GET_NEXT_LINE = get_next_line/get_next_line.c \
get_next_line/get_next_line_utils.c


SRC = cub3D          \
	  map            \
	  draw_minimap   \
	  color          \

ADD = $(addsuffix .c, $(addprefix src/, $(SRC)))
ADD += $(GET_NEXT_LINE)

OBJ = $(ADD:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	
	make -C $(MLX_DIR)
	make -C $(LIBFT_DIR)
	$(CC) -o $(NAME) $(OBJ) $(LIBFT) $(MLX_FLAGS)

