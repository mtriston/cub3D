COM_COLOR   = \033[0;34m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m

OK_STRING    = [OK]
COM_STRING   = Compiling

NAME = cub3D

SRC_DIR = src/
OBJ_DIR = bin/
HDR_DIR = includes/
LIB_DIR = libs/

INCLUDES = -I$(HDR_DIR)

CC = gcc
CFLAGS = -Wall -Werror -Wextra -O2 -g

MLX_DIR = $(LIB_DIR)/minilibx-linux
MLX_FLAGS = -L $(MLX_DIR) -lmlx -L /usr/include/../lib -lXext -lX11 -lm -lbsd
LIBFT_DIR = $(LIB_DIR)/libft
LIBFT_FLAGS = -L $(LIBFT_DIR) -lft

FILES = cub3d        \
      parser         \
	  parse_map      \
	  exit			 \
	  setup			 \
	  render		 \
	  draw_utils     \
	  validator      \
	  texture        \
	  raycast        \
	  sprite		 \
	  color          \
	  bitmap	     \

SRC_FILES = $(addsuffix .c, $(addprefix $(SRC_DIR), $(FILES)))

OBJ_FILES = $(addsuffix .o, $(addprefix $(OBJ_DIR), $(FILES)))

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ_FILES)
	@make -C $(MLX_DIR)
	@make -C $(LIBFT_DIR)
	@$(CC) -o $(NAME) $(INCLUDES) $(OBJ_FILES) $(LIBFT_FLAGS) $(MLX_FLAGS)
	@echo "$(OK_COLOR) $(OK_STRING) $(OBJ_COLOR) $(NAME) $(NO_COLOR)"

$(OBJ_FILES): $(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(COM_COLOR) $(COM_STRING) $(OBJ_COLOR) $(@) $(NO_COLOR)"

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_FILES)
	@echo "$(WARN_COLOR) All object files have been removed $(NO_COLOR)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(WARN_COLOR) $(NAME) has been removed $(NO_COLOR)"

re: fclean all

bonus: all

run: re 
	./cub3D map.cub
