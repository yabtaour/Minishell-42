#include "../minishell.h"

int close_pipes(int **pip, int lent)
{
    int idx;

    idx = -1;
    while (++idx < lent - 1)
    {
        close(pip[idx][1]);
        close(pip[idx][0]);
    }
    return (0);
}

int ft_dup(int lent, t_cmd *lst_cmd, int **pip)
{
    dup2(lst_cmd->fd_in, 0);
    dup2(lst_cmd->fd_out, 1);
    if (lst_cmd->fd_in != 0)
        close(lst_cmd->fd_in);
    if (lst_cmd->fd_out != 1)
        close(lst_cmd->fd_out);
    return (0);
}