NAME = cub3D

# Compiler and flags
CC = gcc
CFLAGS = -g -fsanitize=address #-Wall -Wextra -Werror

# Sources
SRCS = \
	cub3D.c \
	./parser/helper.c ./parser/helper1.c ./parser/helper2.c ./parser/helper3.c ./parser/helper4.c ./parser/helper5.c ./parser/helper6.c ./parser/doors.c \
	./utils/ft_split.c ./utils/ft_strdup.c ./utils/ft_strcmp.c ./utils/ft_strtrim.c ./utils/ft_isspace.c ./utils/ft_split2.c ./utils/ft_isdigit.c \
	./utils/ft_atoi.c ./utils/get_next_line.c ./utils/ft_memset.c ./utils/ft_strchr.c ./utils/ft_lstnew.c ./utils/ft_lstaddback.c ./parser/texture_helper.c\
	./utils/ft_strjoin.c ./utils/ft_strlen.c ./utils/ft_substr.c ./utils/ft_lstsize.c ./utils/ft_strcpy.c ./parser/texture.c\
	./parser/flood_fill.c ./parser/sprite_animation.c ./parser/sprite_init.c ./parser/sprite_init_helper.c ./parser/sprite_render.c\
	./parser/weapon.c ./parser/weapon_helper.c\
	src/minimap.c src/minimap_utils.c src/minimap_draw.c src/minimap_init.c src/rays.c src/3d.c src/helper_minimap.c\

OBJS = $(SRCS:.c=.o)

ARCH := $(shell uname -m)
UNAME_S := $(shell uname -s)

ifeq ($(ARCH),arm64)
	BREW_PATH = /opt/homebrew
else
	BREW_PATH = /usr/local
endif

# MLX42 setup
MLX_DIR = ./MLX42
MLX_BUILD = $(MLX_DIR)/build
MLX_LIB = $(MLX_BUILD)/libmlx42.a
MLX_INC = -I$(MLX_DIR)/include

# OS-specific settings
ifeq ($(UNAME_S),Linux)
	# Linux settings
	GLFW_FLAGS = $(shell pkg-config --libs glfw3 2>/dev/null || echo "-lglfw")
	GLFW_INC = $(shell pkg-config --cflags glfw3 2>/dev/null)
	MLX_FLAGS = $(GLFW_FLAGS) -ldl -pthread -lm
else ifeq ($(UNAME_S),Darwin)
	# macOS settings
	GLFW_PATH = $(BREW_PATH)/opt/glfw
	ifeq ($(wildcard $(GLFW_PATH)/lib/libglfw.*),)
		GLFW_FLAGS = $(shell pkg-config --libs glfw3 2>/dev/null || echo "-lglfw")
		GLFW_INC = $(shell pkg-config --cflags glfw3 2>/dev/null)
	else
		GLFW_FLAGS = -L$(GLFW_PATH)/lib -lglfw
		GLFW_INC = -I$(GLFW_PATH)/include
	endif
	MLX_FLAGS = $(GLFW_FLAGS) -framework Cocoa -framework OpenGL -framework IOKit
endif

all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	@echo "Building MLX42..."
	@cmake -S $(MLX_DIR) -B $(MLX_BUILD)
	@cmake --build $(MLX_BUILD)

%.o: %.c
	@$(CC) $(CFLAGS) $(MLX_INC) $(GLFW_INC) -c $< -o $@

$(NAME): $(OBJS)
	@echo "Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) $(MLX_FLAGS) $(MLX_INC) -o $(NAME)
	@echo "✓ $(NAME) built successfully!"

clean:
	@rm -f $(OBJS)
	@echo "✓ Object files cleaned"

fclean: clean
	@rm -f $(NAME)
	@echo "✓ $(NAME) removed"

re: fclean all

.PHONY: all clean fclean re