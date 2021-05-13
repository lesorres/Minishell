#include "minishell.h"

int main(int argc, char const **argv)
{
    char    str[2000];
    int     l;
    struct termios term;

    tcgetattr(0, &term);
    term.c_lflag &= ~(ECHO);
    term.c_lflag &= ~(ICANON);
    tcsetattr(0, TCSANOW, &term);
    tgetent(0, TERM_NAME);

    char *ed = tigetstr("ed");
    while (ft_strcmp(str, "\4"))
    {
        ft_putchar_fd(save_cursor, 1);
        do {
            l = read(0, str, 100);
            if (!ft_strcmp(str, "\e[A"))
            {
                ft_putchar_fd(restore_cursor, 1);
                ft_putchar_fd(*ed, 1);
                write(1, "prev", 4);
            }
            else if (!ft_strcmp(str, "\e[B"))
            {
                ft_putchar_fd(restore_cursor, 1);
                ft_putchar_fd(*ed, 1);
                write(1, "next", 4);
            }
            else if (!ft_strcmp(str, key_backspace) || ft_strcmp(str, "\177"))
            {
                ft_putchar_fd(cursor_left, 1);
                ft_putchar_fd(*ed, 1);
            }
            else
                write(1, str, l);
        } while (ft_strcmp(str, "\n") || ft_strcmp(str, "\4"));
    }
    write(1, "\n", 1);
    return (0);
}