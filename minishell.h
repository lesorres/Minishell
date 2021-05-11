#include <stdio.h>
#include <unistd.h>
#include "libft/libft.h"
#include "get_next_line.h"

// typedef struct s_flags
// {
//     char *flag;
// } t_flags;


typedef struct s_command
{
	char	*flag;
	char	*buildin_cmd;
	int		echo;
	int		cd;
	int		pwd;
	int		export;
	int		unset;
	int		env;
	int		exit;
}   t_command;