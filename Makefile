
NAME		:= minishell

LIBFT		:= libft.a
LIBFT_PATH	:= lib/libft

CC			:= cc

CFLAGS		:= -Wall -Werror -Wextra -g

BUILTINS	:=	builtins/env.c \
				builtins/env_tools.c \

CLEANING	:=	

EXPANDER	:= expander/exp_tools.c \
				expander/expand.c \
				expander/heredoc_exp.c \
				expander/args_split.c

EXEC		:=	executer/exec_tools.c \
				executer/exec.c \
				executer/init_exec_tree.c

PARSER		:=	parser/parser_cleaner.c \
				parser/parser_err.c \
				parser/parser_tools.c \
				parser/parser_nodes.c \
				parser/parser_utils.c \
				parser/parser.c

TOKENIZER	:=	tokenizer/tokenizer_tools.c \
				tokenizer/token.c \
				tokenizer/tokenizer_utils.c \
				tokenizer/token_append.c \
				tokenizer/tokenizer.c

SRCS		:=	$(BUILTINS)\
				$(CLEANING)\
				$(EXEC)\
				$(EXPANDER)\
				$(PARSER)\
				$(TOKENIZER)\
				main.c

OBJS		:=	$(SRCS:.c=.o)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -Iinclude  

all: $(NAME)

$(LIBFT):
	@make bonus -C $(LIBFT_PATH)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) -L$(LIBFT_PATH) -lft  -lreadline

clean:
	@make clean -C $(LIBFT_PATH)
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re