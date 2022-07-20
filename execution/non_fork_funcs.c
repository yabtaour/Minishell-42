#include "../minishell.h"

int non_fork_funcs(t_data *data, t_cmd *cmd)
{
    if (strcmp(cmd->cmd[0], "cd") == 0)
        cd(data, cmd);
    else if (strcmp(cmd->cmd[0], "export") == 0 && !cmd->next)
        export(data, cmd, 1);
    else if (strcmp(cmd->cmd[0], "env") == 0 && !cmd->next)
        ft_print_env(data->lst_env, 0, 1);
    return (0);
}