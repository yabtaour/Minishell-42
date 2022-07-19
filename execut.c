#include "minishell.h"

// this function return a message or not with a number (echo $?)
// zero if sccucss, 127 if cmd not found.
void	exit_status(int status, char *error_messg, t_data *data)
{
	data->ex_code = status;
	if (error_messg != NULL && status != 0)
		printf("%s\n", error_messg);
}

// this function get the path and splited to parts through ':'
void	ft_get_paths(t_data *data)
{
	int		idx = 0;
	char	*path;
	path = ft_get_env(data, "PATH");
	if (path)
		data->paths = ft_split(path, ':');
}
// this func check if the cmd is exist or not
// right now for testing if the cmd do not exist it return a messg with exit status
// if cmd exist it get exuxte
char	*ft_cmd_exist(t_data *data, t_cmd *lst_cmd)
{
	int		idx;
	int		cmd_nb;
	char	*path;
	int		FOUND;

	idx = 0;
	FOUND = 0;
	while (data->paths[idx] && FOUND == 0)
	{
	 	path = ft_strjoin(data->paths[idx], "/");
		path = ft_strjoin(path, lst_cmd->cmd[0]);
		if (access(path, F_OK) == 0){
			FOUND = 1;
			break;
		}
		idx++;
		free(path);
	}
	if (FOUND == 1)
		return (path);
	else
	{
		return (exit_status(127, "Error: Command not found", data), NULL);
	}
	return (NULL);
}


int	ft_if_builtin(t_data *data, t_cmd *lst_cmd)
{
	if (strcmp(lst_cmd->cmd[0], "cd") == 0)
		data->ex_code = cd(data, lst_cmd);
	else if (strcmp(lst_cmd->cmd[0], "echo") == 0)
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
		return (69);
	exit (data->ex_code);
}

int	ft_exe_cmd(t_data *data, char *path, t_cmd *lst_cmd)
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

// int	**fd_ptr(t_data *data, t_cmd *lst_cmd, int lent)
// {
// 	int	idx;
// 	int **pip;
// 	int	old_input;
// 	int	old_output;
// 	t_cmd *cmd_clone;

// 	if (lst_cmd)
// 	{
// 		pip = malloc((lent - 1) * sizeof(int*));
// 		for (int i = 0; i < lent; i++)
// 			pip[i] = malloc(2 * sizeof(int));
// 		cmd_clone = lst_cmd;
// 		idx = 0;
// 		while (idx < lent - 1)
// 		{
// 			pipe(pip[idx]);
// 			idx++;
// 		}
// 		idx = 0;
// 		while (cmd_clone)
// 		{
// 			old_input = cmd_clone->fd_in;
// 			old_output = cmd_clone->fd_out;
// 			if (idx == 0 && !cmd_clone->next)
// 			{
// 				cmd_clone->fd_in = 0;
// 				cmd_clone->fd_out = 1;
// 			}
// 			else if (idx == 0 && cmd_clone->next)
// 			{
// 				cmd_clone->fd_in = 0;
// 				cmd_clone->fd_out = pip[idx][1];
// 			}
// 			else if (idx != 0 && cmd_clone->next)
// 			{
// 				cmd_clone->fd_in = pip[idx - 1][0];
// 				cmd_clone->fd_out = pip[idx][1];
// 			}
// 			else if (idx != 0 && !cmd_clone->next)
// 			{
// 				cmd_clone->fd_in = pip[idx - 1][0];
// 				cmd_clone->fd_out = 1;
// 			}
// 			if (old_input != 0)
// 				cmd_clone->fd_in = old_input;
// 			if (old_output != 1)
// 				cmd_clone->fd_out = old_output;
// 			cmd_clone = cmd_clone->next;
// 			idx++;
// 		}
// 	}
// 	return (pip);
// }

int	*fd_ptr(t_data *data, t_cmd *lst_cmd, int lent)
{
	t_cmd *cmd_clone;
	int		red_fd_inp;
	int		red_fd_out;
	int		*pip;
	int		idx;

	idx = 0;
	cmd_clone = lst_cmd;
	pip = malloc(sizeof(int) * 2);
	if (!pip)
		return (0);
	pipe(pip);
	while (lent > 1 && cmd_clone)
	{
		red_fd_inp = cmd_clone->fd_in;
		red_fd_out = cmd_clone->fd_out;
		if (idx == 0 && cmd_clone->next)
			cmd_clone->fd_out = pip[1];
		else if (idx != 0 && cmd_clone->next)
		{
			cmd_clone->fd_in = pip[0];
			cmd_clone->fd_out = pip[1];
		}
		else if (idx != 0 && !cmd_clone->next)
		{
			cmd_clone->fd_in = pip[0];
			cmd_clone->fd_out = 1;
		}
		if (red_fd_inp != 0)
			cmd_clone->fd_in = red_fd_inp;
		if (red_fd_out != 1)
			cmd_clone->fd_out = red_fd_out;
		idx++;
		cmd_clone = cmd_clone->next;
	}
	return (pip);
}

//  this main only for testing.
int	exe(t_data *data)
{
	char	*cmd_path;
	t_fds fd_lst;
	int	idx;
	int pid;
	int status;
	int id2;

	idx = 0;
	pid = -69;
	id2 = 0;
	data->ex_code = 69;
	cmd_path = NULL;

	int lent = cmds_lent(data);
	HERE
	int *pip = fd_ptr(data, data->lst_cmd, lent);
	t_cmd *cmd_clone = data->lst_cmd;
	ft_get_paths(data);
	int cmd_status;
	// change to clone
	if (data->lst_cmd){
		while (data->lst_cmd)
		{
			if (pid != 0)
			{
				idx++;
				pid = fork(); 
			}
			if (pid == 0 && data->ex_code == 69)
			{
				dup2(data->lst_cmd->fd_in, 0);
				dup2(data->lst_cmd->fd_out, 1);
				close(pip[0]), close(pip[1]);
				free(pip);
				data->ex_code = ft_if_builtin(data, data->lst_cmd);
				if (data->ex_code == 69)
					cmd_path = ft_cmd_exist(data ,data->lst_cmd);
				if (cmd_path)
				{
					data->ex_code = 0;
					ft_exe_cmd(data, cmd_path, data->lst_cmd);
				}
			}
			data->lst_cmd = data->lst_cmd->next;
		}
			close(pip[0]), close(pip[1]);
		while (cmd_clone)
		{
			if (cmd_clone->fd_in != 0)
				close(cmd_clone->fd_in);
			if (cmd_clone->fd_out != 1)
				close(cmd_clone->fd_out);
			cmd_clone = cmd_clone->next;
		}
		free(pip);
		while (id2 < idx)
		{
			pid = waitpid(-1, &status ,0);
			if (WIFEXITED(status) && WEXITSTATUS(status) != -1 && pid != -1)
				kill(pid, SIGINT);
			id2++;
		}
	}
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
