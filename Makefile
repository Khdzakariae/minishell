FLAGS = -Wall -Wextra -Werror

NAME = minishell

LIBFT = lib/libft/libft.a

INCLUDES = -I "includes/"

SRC_1_2 = sources/main.c sources/minishell.c sources/utility_functions.c sources/parssin/syntax_error.c \
			sources/parssin/tokenization.c sources/parssin/handle_signals.c sources/parssin/parse_symbol.c

OBJ = $(SRC_1_2:.c=.o)

all: $(LIBFT) $(NAME) 
	@echo "minishell done by success [ ✅ ]"

$(LIBFT) :
	@make -C lib/libft --silent
	@echo "libft done [ ✅ ]"

%.o : %.c
	@cc  $(FLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ)
	@cc $(FLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

clean:
	@rm -f $(OBJ)
	@make clean -C lib/libft --silent
	@echo "clean [ ✅ ]"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C lib/libft --silent
	@echo "fclean [ ✅ ]"

re: fclean all
