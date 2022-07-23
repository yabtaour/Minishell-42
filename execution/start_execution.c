#include "../minishell.h"

int	ft_wait_nd_kill(int	idx)
{
	int	pid;
	int	status;

	while (idx > 0)
	{
		pid = waitpid(-1, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != -1 && pid != -1)
			kill(pid, SIGINT);
		idx--;
	}
	return (0);
}

int	start_execution(t_data *data, int **pip)
{
	t_cmd	*cmd_clone;
	char	*cmd_path;
	int		status;
	int		idx;
	int		pid;

	cmd_clone = data->lst_cmd;
	cmd_path = NULL;
	idx = 0;
	pid = -42;
	status = 0;
	while (cmd_clone)
	{
		data->error = non_fork_funcs(data, cmd_clone);
		if (pid != 0 && data->error != 0)
		{
			idx++;
			pid = fork();
		}
		if (pid == 0 && cmd_clone->fd_in != -69)
		{
			ft_dup(data->lent, cmd_clone, pip);
			close_pipes(pip, data->lent);
			data->error = ft_if_builtin(data, cmd_clone);
			if (data->error == 2)
				cmd_path = ft_cmd_exist(data, cmd_clone, 0);
			if (cmd_path)
				ft_execute_cmd(data, cmd_path, cmd_clone);
			exit(1);
		}
		cmd_clone = cmd_clone->next;
	}
	close_pipes(pip, data->lent);
	close_fds(data->lst_cmd);
	ft_wait_nd_kill(idx);
	// while (idx > 0)
	// {
	// 	pid = waitpid(-1, &status, 0);
	// 	if (WIFEXITED(status) && WEXITSTATUS(status) != -1 && pid != -1)
	// 		kill(pid, SIGINT);
	// 	idx--;
	// }
	return (0);
}
