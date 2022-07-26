#include "minishell.h"

void handler(int sig)
{
    // printf("%d\n", test);
    if (where_ami == 1)
    {
        if (sig == SIGINT)
        {
  		    rl_replace_line("", 0);
		    write(1, "\n", 1);
		    rl_on_new_line();
		    rl_redisplay();
        }
        if (sig == SIGQUIT)
            signal(SIGQUIT, SIG_IGN);
        return;
    }
}