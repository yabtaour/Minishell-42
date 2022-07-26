#include "minishell.h"

void handler(int sig)
{
    if (sig == SIGINT)
    {
  		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
    }
}

void handler2(int sig)
{
    if (sig == SIGINT)
    {
        close(0);
        close(1);
        // write(2 ,  "\n" , 1);
  		// rl_replace_line("", 0);
		// write(1, "\n", 1);
		// rl_on_new_line();
		// rl_redisplay();
        exit(1);

    }
}

int init_signals(t_data *data, int process)
{

    if (process == 0)
    {
        rl_catch_signals = 0;
        signal(SIGQUIT, SIG_IGN);
        signal(SIGINT, handler);
    }
    else 
    {
        // rl_catch_signals = 1;
        signal(SIGINT, handler2);
        // signal(SIGQUIT);
    }
    return (0);
}