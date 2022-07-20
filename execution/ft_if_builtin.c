#include "../minishell.h"

int	ft_if_builtin(t_data *data, t_cmd *lst_cmd)
{
	if (strcmp(lst_cmd->cmd[0], "echo") == 0)
		data->ex_code = echo(data, lst_cmd, 1);
	else if (strcmp(lst_cmd->cmd[0], "pwd") == 0)
		data->ex_code = pwd(data, lst_cmd, 1);
	else if (strcmp(lst_cmd->cmd[0], "unset") == 0)
		data->ex_code = unset(data, lst_cmd);
	else if (strcmp(lst_cmd->cmd[0], "export") == 0)
		data->ex_code = export(data, lst_cmd, 1);
	else if (strcmp(lst_cmd->cmd[0], "env") == 0)
		ft_print_env(data->lst_env, 0, 1);
	else
		return (2);
	exit (data->ex_code);
}