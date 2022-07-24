#include "../minishell.h"

int	non_fork_funcs(t_data *data, t_cmd *cmd, int **pip)
{
	if (ft_herdoc(data, cmd, pip) == 1)
		return (1);
	if (cmd->cmd && cmd->cmd[0])
	{
		if (strcmp(cmd->cmd[0], "cd") == 0)
			data->error = cd(data, cmd);
		else if (strcmp(cmd->cmd[0], "export") == 0 && !cmd->next)
			data->error = export(data, cmd, 1);
		else if (strcmp(cmd->cmd[0], "env") == 0 && !cmd->next)
			ft_env_built(data);
		else
			return (-666);
	}
	return (data->error);
}
