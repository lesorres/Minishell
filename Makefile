# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fhyman <fhyman@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/16 20:26:07 by kmeeseek          #+#    #+#              #
#    Updated: 2021/07/10 22:45:20 by fhyman           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIB = ./libft/libft.a
HEAD = *.h
#BUILDINS = ./buildin/buildin.c ./buildin/cmd_exit.c ./buildin/cmd_export.c ./buildin/cmd_cd.c ./buildin/cmd_env.c ./buildin/cmd_echo.c ./buildin/cmd_pwd.c ./buildin/cmd_unset.c ./buildin/export_utils.c ./buildin/cd_utils.c ./buildin/buildin_part2.c ./buildin/buildin_part3.c
BUILDINS = $(wildcard ./buildin/*.c)
#INPUT = main.c signals.c pipe_exec.c
INPUT = $(wildcard ./execute/*.c)
# PARSER = parser/parser.c parser/parser_dollar_sign.c parser/parser_redirections.c parser/parser_mem_alloc.c parser/parser_quotes.c parser/parser_utils.c
PARSER = $(wildcard ./parser/*.c)
FLAGS = -ltermcap
CFLAGS	= -Wall -Wextra -Werror
RM = rm -f
AR = ar rc
OBJS = $(INPUT:.c=.o)
OBJS_BUILDIN = $(BUILDINS:.c=.o)
OBJS_PARSER = $(PARSER:.c=.o)
NORM = norminette *.[h] ./parser/*.[ch] ./buildin/*.[ch] ./execute/*.[ch] ./libft/*.[ch]

all: lib $(NAME)
$(NAME): $(OBJS) $(OBJS_BUILDIN) $(OBJS_PARSER) $(LIB) 
	gcc -g $(OBJS) $(OBJS_BUILDIN) $(OBJS_PARSER) $(LIB) $(FLAGS) $(CFLAGS) -o $(NAME)
lib:
	@$(MAKE) -C ./libft
%.o: %.c %.h
	gcc -g $(CFLAGS) -c $< -o $(<:.c=.o)
norm:
	@$(NORM)
clean:
	@$(MAKE) clean -C ./libft
	@$(RM) $(OBJS) $(OBJS_BUILDIN) $(OBJS_PARSER)
fclean: clean
	@$(MAKE) fclean -C ./libft
	@$(RM) $(NAME)
re: fclean all
.PHONY: all clean fclean re norm lib