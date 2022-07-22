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
    struct sigaction sa;

    sa.sa_sigaction = handler;
    sigaction(SIGINT, &sa, NULL);
    return (0);
}