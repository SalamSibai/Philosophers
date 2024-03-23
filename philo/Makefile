NAME			= philo

SRC_DIR			= .
PARSE_DIR		= ../parsing

SRC_FILES		= $(SRC_DIR)/main.c \
				$(PARSE_DIR)/ft_split.c \
				$(PARSE_DIR)/parsing.c \
				$(PARSE_DIR)/ft_join.c \
				$(PARSE_DIR)/parsing_utils.c \
				$(PARSE_DIR)/parsing_error.c \
				$(SRC_DIR)/error_handler.c \

OBJS			= $(SRC_FILES:.c=.o)

CC				= gcc
CFLAGS			= -Wall -Werror -Wextra -fsanitize=address -g3

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re