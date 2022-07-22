NAME	= minishell
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
FILES	= $(wildcard *.c)
LIBFT	= libft/libft.a

all : run

run : makediff
	@$(CC) -o $(NAME) $(FILES) $(CFLAGS) $(LIBFT) -lreadline
makediff :
	@make -C libft

clear :
	@rm -rf $(NAME)

fclean : clear
	@make fclean -C libft

re : fclean all

.PHONY : all run makediff clear fclean re