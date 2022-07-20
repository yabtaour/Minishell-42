#include "../minishell.h"

int	ft_execute_cmd(t_data *data, char *path, t_cmd *lst_cmd)
{
	if (lst_cmd->fd_in != 0)
		close(lst_cmd->fd_in);
	if (lst_cmd->fd_out != 1)
		close(lst_cmd->fd_out);
	execve(path, lst_cmd->cmd, data->env);
	return (0);
}

int	cmds_lent(t_data *data)
{
	int	lent;
	t_cmd *cmd_clone;

	lent = 0;
	cmd_clone = data->lst_cmd;
	while (cmd_clone)
	{
		lent++;
		cmd_clone = cmd_clone->next;
	}
	return (lent);
}



//  this main only for testing.
int	execution(t_data *data)
{
	int	idx;
	int	**pip;
	int	lent;
	int	pid;

	idx = 0;
	pid = 0;
	lent = cmds_lent(data);
	pip = ft_init_pipes(data, data->lst_cmd, lent);
	ft_get_paths(data);
	if (data->lst_cmd)
		start_execution(data, lent, pip);
	return (0);
}






















// --------------------------------------------------------------------------------------- //

// 	int lent = cmds_lent(data);
// 	int	idx2;
// 	int pip[lent][2];
// 	t_cmd *cmd_clone;

// 	cmd_clone = data->lst_cmd;
// 	idx2 = 0;
// 	while (idx2 < lent )
// 	{
// 		pipe(pip[idx2]);
// 		idx2++;
// 	}
// 	idx2 = 0;
// 	while (cmd_clone)
// 	{
// 		if (idx2 == 0 && !cmd_clone->next)
// 		{
// 			cmd_clone->fd_in = 0;
// 			cmd_clone->fd_out = 1;
// 		}
// 		else if (idx2 == 0 && cmd_clone->next)
// 		{
// 			cmd_clone->fd_in = 0;
// 			cmd_clone->fd_out = pip[idx2][1];
// 		}
// 		else if (idx2 != 0 && cmd_clone->next)
// 		{
// 			cmd_clone->fd_in = pip[idx2 - 1][1];
// 			cmd_clone->fd_out = pip[idx2][1];
// 		}
// 		else if (idx2 != 0 && !cmd_clone->next)
// 		{
// 			cmd_clone->fd_in = pip[idx2 - 1][1];
// 			cmd_clone->fd_out = 1;
// 		}
// 		// printf("[ CMD\t:\t%s] | [FD OUT\t:\t%d] | [FD IN\t:\t%d]\n", cmd_clone->cmd[0], cmd_clone->fd_out, cmd_clone->fd_in);
// 		cmd_clone = cmd_clone->next;
// 		idx2++;
// 	}

// // --------------------------------------------------------------------------------------- //
