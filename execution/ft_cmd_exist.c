#include "../minishell.h"

// this func check if the cmd is exist or not
// right now for testing if the cmd do 
// not exist it return a messg with NULL
// if cmd exist it get exuxte

int	check_result(int found)
{
	if (found == 1)
		return (1);
	else
		ft_putstr_fd("mshell: command not found\n", 2);
	return (0);
}

char	*ft_cmd_exist(t_data *data, t_cmd *lst_cmd, int idx)
{
	int		cmd_nb;
	char	*path;
	int		found;

	found = 0;
	path = NULL;
	if (access(data->lst_cmd->cmd[0], F_OK) == 0)
		return (data->lst_cmd->cmd[0]);
	while (data->paths[idx] && found == 0)
	{
		path = ft_strjoin(data->paths[idx], "/");
		path = ft_strjoin(path, lst_cmd->cmd[0]);
		if (access(path, F_OK) == 0)
		{
			found = 1;
			break ;
		}
		else
			free(path);
		idx++;
	}
	if (check_result(found) == 1)
		return (path);
	return (NULL);
}
