#include "minishell.h"

void handler(int sig)
{
    if (sig == SIGINT)
    {
  		rl_replace_line("", 0);
		write(STDIN_FILENO, "\n", 1);
		rl_on_new_line();
		rl_redisplay();

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