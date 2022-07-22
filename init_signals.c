#include "minishell.h"

void handler(int sig)
{
    if (sig == SIGINT)
    {
        ft_putstr_fd("HAHA", 1);
    }
}

int init_signals(t_data *data)
{
    if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
        printf("NO SIGINT");
    if (signal(SIGINT, handler) == SIG_ERR)
        printf("NOT SIGQUIT");
    return (0);
}