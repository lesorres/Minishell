# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fhyman <fhyman@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/16 20:26:07 by kmeeseek          #+#    #+#              #
#    Updated: 2021/05/16 20:29:57 by fhyman           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIB = ./libft/libft.a
HEAD = *.h
INPUT = main1.c ft_strcmp.c
FLAGS = -ltermcap -g -Wall -Werror -Wextra 
RM = rm -f
AR = ar rc
OBJS = $(INPUT:.c=.o)
.c.o:
	cc -c $< -o $(<:.c=.o)
all: $(NAME)
$(NAME): $(OBJS)
	$(MAKE) -C ./libft
	gcc $(OBJS) $(LIB) $(FLAGS) -o $(NAME)
clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJS)
fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME)
re: fclean all
.PHONY: all clean fclean re