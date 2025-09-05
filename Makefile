NAME = cub3D
CC = gcc
CFLAGS =  -fsanitize=address -g

SRCS = cub3D.c ./utils/ft_split.c ./utils/ft_strcpy.c ./utils/ft_strdup.c ./utils/ft_strjoin.c ./utils/ft_strlen.c ./utils/ft_substr.c ./utils/ft_strchr.c\
	./utils/ft_strcmp.c ./utils/ft_strtrim.c ./utils/ft_isspace.c ./utils/ft_split2.c ./utils/ft_isdigit.c ./utils/ft_atoi.c ./utils/get_next_line.c\

OBJS = $(SRCS:.c=.o)

all = $(NAME)

$(NAME): $(OBJS) cub3D.h
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean
