NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS =	srcs/main.c \
		srcs/signals/signals.c \
		srcs/utils/env_utils.c \
		srcs/utils/errors.c \
		srcs/utils/string_utils.c \
		srcs/parser/tokenize.c \
		srcs/parser/tokenize_utils.c \
		srcs/parser/token_free.c \
		srcs/parser/split_pipes.c \
		srcs/parser/cmd_utils.c \
		srcs/parser/expand.c \
		srcs/parser/redir_utils.c \
		srcs/parser/redir_parse.c \
		srcs/parser/syntax.c \
		srcs/executor/find_path.c \
		srcs/executor/execute.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re