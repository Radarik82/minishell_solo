NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline

INCLUDES = -Iincludes/ -Ilibft/

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS =	srcs/main.c \
		srcs/signals/signals.c \
		srcs/utils/env_utils.c \
		srcs/utils/errors.c \
		srcs/utils/string_utils.c \
		srcs/executor/builtin_cmds.c \
		srcs/executor/builtin_utils.c \
		srcs/executor/execute_pipes.c \
		srcs/executor/execute.c \
		srcs/executor/find_path.c \
		srcs/executor/redirections.c \
		srcs/executor/setup_pipes.c \
		srcs/parser/tokenize.c \
		srcs/parser/split_pipes.c \
		srcs/parser/split_pipes_utils.c \
		srcs/parser/parse_pipeline.c

OBJ_DIR = obj
OBJS = $(SRCS:srcs/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: srcs/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

# %.o: %.c
# 	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
