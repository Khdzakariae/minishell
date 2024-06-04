FLAGS = -Wall -Wextra -Werror

NAME = minishell

INCLUDES = -I "includes/"

SRC_1_2 = sources/minishell.c

OBJ = $(SRC_1_2:.c=.o)

all: $(NAME)
	@echo "minishell done by success [ ✅ ]"

%.o : %.c
	@cc $(FLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ)
	@cc $(FLAGS) $(OBJ) -o $(NAME)

clean:
	@rm -f $(OBJ)
	@echo "clean [ ✅ ]"

fclean: clean
	@rm -f $(NAME)
	@echo "fclean [ ✅ ]"

re: fclean all
