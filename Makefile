# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/28 18:51:17 by yelu              #+#    #+#              #
#    Updated: 2025/04/28 18:51:17 by yelu             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
RED		=	\033[1;31m
GREEN	=	\033[1;32m
YELLOW	=	\033[1;33m
BLUE	=	\033[1;34m
PINK 	=	\033[1;35m
RESET	=	\033[0m
CLEAR_LINE = \033[2K


# Program name
NAME = cub3D

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
LIBFT_DIR = libft
MLX_DIR = minilibx-linux
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a
INC = -I$(INC_DIR)

# Directories of Parsing
SRC_PARSING = parsing

# Directories of Raycasting
SRC_RAYCASTING = raycasting

# Directories of Utils
SRC_UTILS = utils

# Compiler & flags
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 #-fsanitize=address
RM = rm -rf

# Source files
SRC = $(addprefix $(SRC_DIR)/, \
		main.c \
		$(addprefix $(SRC_PARSING)/, \
		colours.c \
		map_1.c \
		map_2.c \
		parsing.c \
		player.c \
		search_map_details.c \
		textures.c \
		utils_char.c \
		utils.c) \
		$(addprefix $(SRC_RAYCASTING)/, \
		draw_utils.c \
		movement_utils.c \
		raycasting.c \
		render_utils.c \
		sprite_utils.c \
		window_utils.c) \
		$(addprefix $(SRC_UTILS)/, \
		cleanup.c))

#$(wildcard $(SRC_DIR)/token/*.c)

# Object files
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Build rules
all: $(LIBFT) $(NAME)

$(LIBFT): FORCE
	@echo "$(PINK)=======================================$(RESET)"
	@echo "$(CYAN)  🚀 Building libft...$(RESET)"
	@echo "$(PINK)=======================================$(RESET)"
	@make bonus -C $(LIBFT_DIR)
	@make -C $(MLX_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@printf "$(YELLOW)Compiling\t%-33.33s\r $(GREEN) $(RESET)" $@

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(MLX) -lreadline -I /opt/X11/include -L /opt/X11/lib -lX11 -lXext -lm
	@printf "$(YELLOW) Compiling\t%-33.33s\r $(GREEN) $(RESET)" $@
	@echo "$(GREEN)✅ Build Successful: $(NAME) $(RESET)"

# Build library folder
$(OBJ_DIR): FORCE
	@mkdir -p $(OBJ_DIR)

# Clean object files and executable
clean:
	@echo "$(RED)❌ Deleting\t$(RESET)$(WHITE)Objects$(RESET)\t$(OBJ_DIR)";
	@make clean -C $(LIBFT_DIR) 
	@$(RM) $(OBJ_DIR)
	@echo "$(GREEN)✅ Removed\t$(RESET)$(WHITE)Objects$(RESET)"

fclean: clean
	@echo "$(RED)❌ Deleting libraries$(RESET)"
	@make fclean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)
	@echo "$(RED)❌ Deleting$(RESET)\t$(NAME)"
	@$(RM) $(NAME)
	@echo "$(GREEN)✅ Removed\t$(RESET)$(WHITE)$(NAME)$(RESET)"

re: fclean all

# # debug:
#@echo "SRC: $(SRC)"
#@echo "OBJ: $(OBJ)"
#@echo "OBJ_DIR: $(OBJ_DIR)"

FORCE:

norm :
	@echo "${BLUE}----------NORMINETTE TIME!----------\n${RESET}"
	@echo "${GREEN}----------src----------${RESET}"
	@norminette src
	@echo "${GREEN}\n----------include----------${RESET}"
	@norminette include
	@echo "${GREEN}\n----------libft----------${RESET}"
	@norminette libft
	@echo "${GREEN}\n       ALL CLEAR!✅✅✅\n${RESET}"

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) $(ARG)

fdleaks:
	valgrind --track-fds=yes ./$(NAME) $(ARG)
#example way of writing in terminal : ARG=maps/valid/.cub

.PHONY: all clean fclean re norm FORCE valgrind fdleaks

# -I(include directory) - Tells the compiler to look for header files
# -L(directory) - Tells the compiler to look for .a library path in this folder
# -l(%.a) - Tells the compiler to look for that specified .a file
