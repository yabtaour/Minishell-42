#include "minishell.h"

// this function return a message or not with a number (echo $?)
// zero if sccucss, 127 if cmd not found.
void	exit_status(int status, char *error_messg)
{
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
int	ft_cmd_exist(t_data *data)
{
	int		idx;
	int		cmd_nb;
	char	*path;
	int		FOUND;

	idx = 0;
	cmd_nb = 5;
	FOUND = 0;
	while (idx < cmd_nb && FOUND == 0)
	{
	 	path = ft_strjoin(data->paths[idx], "/");
		path = ft_strjoin(path, data->lst_cmd->cmd[0]);
		// printf("path and cmd is : %s\n", path);
		if (access(path, F_OK) == 0){
			FOUND = 1;
			break;
		}
		idx++;
		free(path);
	}
	printf("the path is %s\n", path);
	printf("The cmd is %s\n", data->lst_cmd->cmd[0]);
	printf("The opt is %s\n", data->lst_cmd->cmd[1]);
	if (FOUND == 1)
		execve(path, data->lst_cmd->cmd, data->env);
	else
		return (exit_status(127, "Error: Command not found"), 127);
	free(path);
	return (0);
}

//  this main only for testing.
int	exe(t_data *data)
{
	int pid;
	// t_data data;

	// data.ac = 0;
	// data.ac = ac;
	// data.av = av;
	// data.env = env;
	// ft_env(&data);
	while (data->lst_cmd)
	{
		ft_get_paths(data);
		
		data->lst_cmd = data->lst_cmd->next;
	}
	// printf("\n%s\n", data->lst_cmd->cmd[0]);
	// pull the data
	// check if the cmds exist in builtin
	// check if the cmds exist in bash
	// exeuct
	return (0);
}