# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fhyman <fhyman@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/16 20:26:07 by kmeeseek          #+#    #+#              #
#    Updated: 2021/05/22 18:38:13 by fhyman           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIB = ./libft/libft.a

HEAD = *.h

INPUT = main.c get_next_line.c get_next_line_utils.c 

FLAGS = -ltermcap -g -Wall -Werror -Wextra 

RM = rm -f

AR = ar rc

OBJS = $(INPUT:.c=.o)

NORM = norminette *.[ch]

.c.o:
	cc -c $< -o $(<:.c=.o)
all: $(NAME)
$(NAME): $(OBJS)
	$(MAKE) -C ./libft
	gcc $(OBJS) $(LIB) $(FLAGS) -o $(NAME)
#	$(NORM)
parser:
	gcc parser_main.c parser.c minishell.h libft/libft.a -g
s_parser:
	gcc parser_main.c parser.c minishell.h libft/libft.a -g -fsanitize=address
clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJS)
fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME)
re: fclean all
.PHONY: all clean fclean re