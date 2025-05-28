CC = cc
CFLAGS = -Wall -Werror -Wextra -g
NAME = minishell
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
RFLAGS = -lreadline -lhistory -lncurses

SRC =	main.c\
	parser/lexer.c\
	cleanup/clean.c\
	cleanup/clean2.c\
	cleanup/clean3.c\
	parser/utils1.c\
	parser/utils2.c\
	parser/parsing.c\
	parser/expand_case.c\
	parser/lexer_utils.c\
	parser/op_handler1.c\
	parser/op_handler2.c\
	parser/parsing_utils.c\
	parser/expand.c\
	builtin/built_in1.c\
	builtin/built_in2.c\
	builtin/built_in_utils.c\
	builtin/export.c\
	builtin/export_utils.c\
	builtin/sort_exp.c\
	external/child.c\
	external/execution.c\
	external/exec_utils.c\
	external/exec_path.c\
	external/hd_expand.c\
	external/redir_utils.c\
	external/expand_utils.c\
	external/external_cmd.c\
	external/external_single.c\
	external/redirections.c\
	external/handle_heredoc.c\
	cleanup/error.c\
	signal.c\
	env_copy.c\

OBJS = $(SRC:%.c=objs/%.o)

all: $(NAME)

libft:
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME) : $(OBJS) | libft
	@$(CC) $(CFLAGS) $^ -o $(NAME) $(LIBFT) $(RFLAGS)

objs/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf objs
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re libft
