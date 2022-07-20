#include "../minishell.h"

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
		printf("Error comds not found\n");
	return (NULL);
}