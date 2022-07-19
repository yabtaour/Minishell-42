#include "../minishell.h"

int	ft_add_redirection(t_data *data, int i)
{
	char	*command;
	int		len;
	int		origin;

	origin = i;
	len = 0;
	command = NULL;
	while (data->cmd[i] && ft_is_redirection(data->cmd[i]))
	{
		i++;
		len++;
	}
	command = ft_substr(data->cmd, origin, len);
	i += len;
	i--;
	data->lst_lexer = ft_add_lexer_back(data->lst_lexer, command, REDIRECTION);
	free(command);
	return (i);
}
