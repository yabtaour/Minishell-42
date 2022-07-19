#include "../minishell.h"

int	ft_add_pipe(t_data *data, int i)
{
	int		origin;
	char	*command;
	int		len;

	origin = i;
	command = NULL;
	len = 0;
	while (data->cmd[i] && data->cmd[i] == '|')
	{
		i++;
		len++;
	}
	command = ft_substr(data->cmd, origin, len);
	i += len;
	i--;
	data->lst_lexer = ft_add_lexer_back(data->lst_lexer, command, PIPE);
	free(command);
	return (i);
}
