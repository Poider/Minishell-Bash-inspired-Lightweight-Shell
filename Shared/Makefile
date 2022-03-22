# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/08 11:02:02 by mel-amma          #+#    #+#              #
#    Updated: 2022/03/04 14:42:41 by mel-amma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = minishell.c helpers.c helpers2.c  wildcard.c
NAME = minishell
FLAG = -lreadline -L /Users/mel-amma/Desktop/homebrew/opt/readline/lib -I /Users/mel-amma/Desktop/homebrew/opt/readline/include  -lncurses -g 
#!-Wall -Wextra -Werror!#
all : $(NAME)

$(NAME): $(SRC)
	@gcc $(FLAG) $(SRC) -o $(NAME)
clean:
	@rm -rf $(NAME)
fclean: clean
re : fclean all
.PHONY: all clean fclean re