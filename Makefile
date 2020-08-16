NAME = cub3D
CC = gcc
CFLAGS = -Wall -Werror -Wextra 

MLX_DIR = ./minilibx-linux
MLX_FLAGS = -L $(MLX_DIR) -lmlx -L /usr/include/../lib -lXext -lX11 -lm -lbsd 
LIBFT = ./libft/libft.a
LIBFT_DIR = ./libft

HEADER = cub3D.h

SRC = cub3D          \
      parser         \
	  parse_map      \
	  error			 \
	  setup			 \
	  draw_minimap   \
	  render		 \
	  texture        \
	  raycast        \
	  sprite		 \
	  color          \

ADD = $(addsuffix .c, $(addprefix src/, $(SRC)))

OBJ = $(ADD:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -g -c $< -o $@

$(NAME): $(OBJ) $(HEADER)
	
	make -C $(MLX_DIR)
	make -C $(LIBFT_DIR)
	$(CC) -g -o $(NAME) $(OBJ) $(LIBFT) $(MLX_FLAGS)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

run: re 
	./cub3D map.cub
