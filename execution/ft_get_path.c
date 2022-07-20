#include "../minishell.h"

// this function get the path and splited to parts through ':'
void	ft_get_paths(t_data *data)
{
	int		idx = 0;
	char	*path;
	path = ft_get_env(data, "PATH");
	if (path)
		data->paths = ft_split(path, ':');
}