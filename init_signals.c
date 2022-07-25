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

// void handler2(int sig)
// {
//     if (sig == SIGINT)
//     {
// 		write(1, "^C\n", 1);
// 		rl_on_new_line();
// 		rl_redisplay();
//     }
// }

int init_signals(t_data *data)
{
    int rl_catch_signals;

    // rl_catch_signals = 0;
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, handler);
    return (0);
}

// int init_signals_child(t_data *data)
// {
//     int rl_catch_signals;

//     // rl_catch_signals = 0;
//     signal(SIGQUIT, SIG_IGN);
//     signal(SIGINT, handler2);
//     return (0);
// }