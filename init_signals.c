#include "minishell.h"

void handler(int sig)
{
    if (sig == SIGINT)
    {
  		// rl_replace_line("", 0);
		// write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
    }
}

int init_signals(t_data *data)
{
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, handler);
    return (0);
}