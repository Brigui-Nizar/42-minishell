NAME	= minishell

# Compiler
CC		= gcc  -g3
CFLAGS	= -Werror -Wextra -Wall

# Libft
LIBFT_PATH	= libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

# Includes
INC			=	-I ./libft/\
				-I ./includes/\

# Sources   sort_basic_insertion/sort_basic_insertion.c
SRC_PATH	=	src/
SRC			=	main.c \
				env/env.c \
				env/env_utils.c \
				errors/minishell_error.c \
				errors/minishell_error_memory.c \
				errors/minishell_error_utils.c \
				errors/minishell_error_input.c \
				errors/minishell_error_exit.c \
				errors/minishell_error_signal.c \
				signal/signal.c \
				signal/signal_fork.c \
				signal/signal_heredoc.c \
				utils/lst.c \
				utils/free.c \
				utils/utils_free.c \
				utils/set_exit_status.c \
				utils/utils_args.c \
				utils/utils_input.c \
				builtins/echo.c \
				builtins/ft_env.c \
				builtins/ft_set.c \
				builtins/pwd.c \
				builtins/unset.c \
				builtins/export.c \
				builtins/execute.c \
				builtins/ft_exit.c \
				builtins/ft_exit_utils.c \
				builtins/ft_bool.c \
				command/init_command.c \
				terminal/init_minishell.c \
				terminal/shell_promt.c \
				terminal/display.c \
				lexer/lexer.c \
				lexer/token.c \
				lexer/utils_lexer_operator.c \
				lexer/utils_lexer_parent.c \
				lexer/utils_lexer_word.c \
				lexer/utils_lexer_single_quote.c \
				lexer/utils_lexer_double_quote.c \
				lexer/utils_lexer_redirection.c \
				lexer/utils_lexer_wildcards.c \
				lexer/utils_lexer_assignment.c \
				lexer/utils_lexer_parse_blank.c \
				lexer/utils_lexer_variable.c \
				lexer/utils_lexer_tilde.c \
				lexer/utils_lexer_end.c \
				lexer/utils_lexer_pipe.c \
				lexer/utils_lexer.c \
				parsing/parser.c \
				parsing/parser2.c \
				parsing/utils_parser_redirection.c \
				parsing/utils_parser_redirec_add.c \
				parsing/utils_parser_ast.c \
				parsing/utils_parser_cmd.c \
				parsing/utils_parser_cmd2.c \
				parsing/wildcards.c \
				parsing/utils_wildcards_match.c \
				parsing/utils_wildcards_extract.c \
				parsing/utils_parser.c \
				exec/execute_ast.c \
				exec/execute_ast2.c \
				exec/execute_command.c \
				exec/execute_operator.c \
				exec/execute_pipe.c \
				exec/execute_redirection.c \
				exec/execute_subshell.c \
				exec/execute_buildargs.c \
				exec/execute_buildargs_helpers.c \
				exec/execute_buildargs_helpers_non_space.c \
				exec/execute_buildargs_utils.c \
				exec/execute_buildargs_utils2.c \
				exec/execute_buildargs_utils_variable.c \
				exec/execute_buildargs_wildcards.c \
				exec/execute_utils.c \
				exec/execute_heredoc.c \
				exec/execute_heredoc2.c \
				builtins/cd.c \
				unexpected_input/is_unexpected.c \
				unexpected_input/utils_handle_check_input.c \
				unexpected_input/utils_is_unexpected.c

SRC_BONUS		=	bonus.c\

SRCS		= $(addprefix $(SRC_PATH), $(SRC))
SRCS_BONUS		= $(addprefix $(SRC_PATH), $(SRC_BONUS))

# Objects
OBJ_PATH	= obj/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))

OBJ_BONUS	= $(SRC_BONUS:.c=.o)
OBJS_BONUS	= $(addprefix $(OBJ_PATH), $(OBJ_BONUS))

# Headers
HEADER = includes/minishell.h \
			includes/structure.h \
			includes/terminal.h \
			includes/token.h \
			includes/builtins.h \
			includes/colors.h \
			includes/env.h \
			includes/errors.h \
			includes/exec.h \
			includes/free.h \
			includes/lexer.h \
			includes/parser.h \
			includes/signals.h \
			includes/utils.h \
			includes/is_unexpected.h 
HEADER_BONUS = includes/minishell.h

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HEADER)
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(OBJ_PATH)test/
	@mkdir -p $(OBJ_PATH)env/
	@mkdir -p $(OBJ_PATH)utils/
	@mkdir -p $(OBJ_PATH)builtins/
	@mkdir -p $(OBJ_PATH)command/
	@mkdir -p $(OBJ_PATH)terminal/
	@mkdir -p $(OBJ_PATH)errors/
	@mkdir -p $(OBJ_PATH)parsing/
	@mkdir -p $(OBJ_PATH)lexer/
	@mkdir -p $(OBJ_PATH)exec/
	@mkdir -p $(OBJ_PATH)signal/
	@mkdir -p $(OBJ_PATH)unexpected_input/
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(LIBFT):
	@echo "Making libft..."
	make -sC $(LIBFT_PATH)

$(NAME):$(LIBFT) $(OBJS)
	@echo "Compiling minishell..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(INC) -lreadline 
	@echo "minishell ready."

bonus: bonus_minishell

bonus_minishell: $(LIBFT) $(OBJS_BONUS)
	@echo "Compiling bonus_minishell..."
	@$(CC) $(CFLAGS) -o bonus_minishell $(OBJS_BONUS) $(LIBFT) $(INC) 
	@echo "pbonus_minishell ready."

clean:
	@echo "Removing .o object files..."
	@rm -rf $(OBJ_PATH)
	@make clean -C $(LIBFT_PATH)

fclean: clean
	@echo "Removing ..."
	@rm -f $(NAME)
	@rm -f checker
	@rm -f $(LIBFT_PATH)$(LIBFT_NAME)

re: fclean all

.PHONY: all re clean fclean

norminette :
	norminette ${SRCS} ${HEADER}

norminette_bonus :
	norminette ${SRCS_BONUS} ${HEADER_BONUS}

norminette_gitingore :
	norminette -R CheckForbiddenSourceHeader --use-gitignore