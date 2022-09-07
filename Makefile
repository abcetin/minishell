NAME	= minishell
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra 
FILES	= $(wildcard *.c built-in/*.c command_process/*.c function_process/*.c pipe/*.c redirect/*.c syntax_control/*.c)
LIBFT	= libft/libft.a

all : run

run : makediff
	@$(CC) -o $(NAME) $(FILES) $(CFLAGS) $(LIBFT) -lreadline 
makediff :
	@make bonus -C libft

clear :
	@rm -rf $(NAME)

fclean : clear
	@make fclean -C libft

re : fclean all

.PHONY : all run makediff clear fclean re