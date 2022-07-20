#include "../minishell.h"

int	start_execution(t_data *data, int lent, int **pip)
{
	t_cmd   *cmd_clone;
	char    *cmd_path;
	int 	status;
	int     idx;
	int     pid;

	cmd_clone = data->lst_cmd;
	cmd_path = NULL;
	idx = 0;
	pid = -42;
	status = 0;
	
	while (cmd_clone)
	{
		data->ex_code = non_fork_funcs(data, cmd_clone);
		if (pid != 0 && data->ex_code != 0)
		{
			idx++;
			pid = fork();
		}
		if (pid == 0 && cmd_clone->fd_in != -69)
		{
			ft_dup(lent, cmd_clone, pip);
			close_pipes(pip, lent);
			data->ex_code = ft_if_builtin(data, cmd_clone);
			if (data->ex_code == 2)
			   cmd_path = ft_cmd_exist(data, cmd_clone);
			if (cmd_path)
				ft_execute_cmd(data, cmd_path, cmd_clone);
			exit(1);
		}
		// printf("The current cmd is [ - %s -] and [ input is [ - %d - ] | output is [ - %d - ] ..... [ next cmd is [- %s -] ]]\n", cmd_clone->cmd[0], cmd_clone->fd_in, cmd_clone->fd_out, cmd_clone->next->cmd[0]);
		cmd_clone = cmd_clone->next;
	}
	close_pipes(pip, lent);
	close_fds(data->lst_cmd);
	while (idx > 0)
	{
		pid = waitpid(-1, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != -1 && pid != -1)
			kill(pid, SIGINT);
		idx--;
	}
	return (0);
}