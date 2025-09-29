NAME = cub3D

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

# Sources
SRCS = \
	cub3D.c \
	./parser/helper.c ./parser/helper1.c ./parser/helper2.c ./parser/helper3.c ./parser/helper4.c ./parser/helper5.c ./parser/helper6.c \
	./utils/ft_split.c ./utils/ft_strdup.c ./utils/ft_strcmp.c ./utils/ft_strtrim.c ./utils/ft_isspace.c ./utils/ft_split2.c ./utils/ft_isdigit.c \
	./utils/ft_atoi.c ./utils/get_next_line.c ./utils/ft_memset.c ./utils/ft_strchr.c ./utils/ft_lstnew.c ./utils/ft_lstaddback.c \
	./utils/ft_strjoin.c ./utils/ft_strlen.c ./utils/ft_substr.c ./utils/ft_lstsize.c ./utils/ft_strcpy.c \
	./parser/flood_fill.c \
	src/minimap.c

OBJS = $(SRCS:.c=.o)

ARCH := $(shell uname -m)

ifeq ($(ARCH),arm64)
	BREW_PATH = /opt/homebrew
else
	BREW_PATH = /usr/local
endif

MLX_DIR = ./MLX42
MLX_BUILD = $(MLX_DIR)/build
MLX_LIB = $(MLX_BUILD)/libmlx42.a
MLX_INC = -I$(MLX_DIR)/include
MLX_FLAGS = -L$(BREW_PATH)/opt/glfw/lib -lglfw -framework Cocoa -framework OpenGL -framework IOKit

all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	@cmake -S $(MLX_DIR) -B $(MLX_BUILD)
	@cmake --build $(MLX_BUILD)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) $(MLX_FLAGS) $(MLX_INC) -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
