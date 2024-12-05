GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
CYAN = \033[0;36m
RESET = \033[0m

NAME = cub3D

LIBFT = libft/libft.a

CC = cc

RM = rm -f

CFLAGS = -Wall -Werror -Wextra -I./includes

MLX_DIR = minilibx-linux

MLX = $(MLX_DIR)/libmlx.a

MLXFLAGS = -lXext -lX11

OBJ_DIR = objs

SRCS = srcs/main.c srcs/utils.c srcs/render.c srcs/map.c srcs/free.c \
		get_next_line/get_next_line_bonus.c \
		get_next_line/get_next_line_utils_bonus.c

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@) # Ensure the directory exists
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(CYAN)Compiling $(YELLOW)$<$(RESET)... $(GREEN)Success$(RESET)"

$(LIBFT):
	@make -s -C ./libft
	@make bonus -s -C ./libft

$(MLX):
	@make -s -C ./minilibx-linux

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) -lm -lX11 -lXext -o $(NAME)
	@echo "$(GREEN)$(NAME) created! 🎉$(RESET)"

clean:
	$(RM) $(OBJS)
	@make clean -s -C ./libft
	@make clean -s -C ./minilibx-linux
	@echo "$(RED)Object files cleaned! 🧹$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)
	@$(RM) $(MLX)
	@echo "$(RED)$(NAME) deleted! 💣$(RESET)"

re: fclean all

.PHONY: fclean all clean re
