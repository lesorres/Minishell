# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fhyman <fhyman@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/16 20:26:07 by kmeeseek          #+#    #+#              #
#    Updated: 2021/06/29 21:12:25 by fhyman           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIB = ./libft/libft.a

BUILDINS = ./buildin/buildin.c ./buildin/cmd_exit.c ./buildin/cmd_export.c ./buildin/cmd_cd.c ./buildin/cmd_env.c ./buildin/cmd_echo.c ./buildin/cmd_pwd.c ./buildin/cmd_unset.c

HEAD = *.h

INPUT = main.c get_next_line.c get_next_line_utils.c parser.c parser_dollar_sign.c signals.c pipe_exec.c parser_redirections.c

FLAGS = -ltermcap -Wall -Werror -Wextra

RM = rm -f

AR = ar rc

OBJS = $(INPUT:.c=.o)

OBJS_BUILDIN = $(BUILDINS:.c=.o)

NORM = norminette *.[ch]

.c.o:
	gcc -g -c $< -o $(<:.c=.o)
all: $(NAME)
$(NAME): $(OBJS) $(OBJS_BUILDIN)
	$(MAKE) -C ./libft
	gcc -g $(OBJS) $(OBJS_BUILDIN) $(LIB) $(FLAGS) -o $(NAME)
#	$(NORM)
parser:
	gcc -g parser_main.c parser.c minishell.h parser_dollar_sign.c libft/libft.a
s_parser:
	gcc parser_main.c parser.c minishell.h parser_dollar_sign.c libft/libft.a -g -fsanitize=address
clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJS) $(OBJS_BUILDIN)
fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME)
re: fclean all
.PHONY: all clean fclean re