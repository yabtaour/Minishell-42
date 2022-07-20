#include "../minishell.h"

int non_fork_funcs(t_data *data, t_cmd *cmd)
{

    if (cmd->cmd)
    {
        if (strcmp(cmd->cmd[0], "cd") == 0)
            data->ex_code = cd(data, cmd);
        else if (strcmp(cmd->cmd[0], "export") == 0 && !cmd->next)
            data->ex_code = export(data, cmd, 1);
        else if (strcmp(cmd->cmd[0], "env") == 0 && !cmd->next)
            ft_env_built(data);
        else
            return (-666);
    }
    return (data->ex_code);
}