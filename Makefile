# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mel-amma <mel-amma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/08 11:02:02 by mel-amma          #+#    #+#              #
#    Updated: 2022/06/26 13:10:07 by mel-amma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = minishell.c helpers.c helpers2.c helpers3.c  wildcard.c\
		built_in_check.c dollar_expansion_1.c dollar_expansion_2.c\
		errors.c expand.c file_openers.c filling.c free_1.c free_2.c get_last_pipe.c\
		handle_exit.c herdoc_reader.c initialize_1.c initialize_2.c\
		line_2_command_table.c pipe_redirection_1.c pipe_redirection_2.c\
		process_files.c process_nodes_1.c process_nodes_2.c process_nodes_3_main.c process_nodes_4.c\
		process_wildcards_util.c process_wildcards.c quotes.c signals.c utils_1.c
		
NAME = minishell
FLAG = -lreadline -L /Users/mel-amma/Desktop/homebrew/opt/readline/lib -I /Users/mel-amma/Desktop/homebrew/opt/readline/include  -lncurses -g -fsanitize=address
#!-Wall -Wextra -Werror!#
all : $(NAME)

$(NAME): $(SRC)
	@gcc $(FLAG) $(SRC) -o $(NAME)
clean:
	@rm -rf $(NAME)
fclean: clean
re : fclean all
.PHONY: all clean fclean re