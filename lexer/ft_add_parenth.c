#include "../minishell.h"

int	ft_add_parenth(t_data *data, int i)
{
	int		origin;
	int		len;
	char	*command;

	origin = i;
	len = 0;
	command = NULL;
	while (data->cmd[i] && ft_is_parenth(data->cmd[i]))
	{
		i++;
		len++;
	}
	command = ft_substr(data->cmd, origin, len);
	i += len;
	i--;
	data->lst_lexer = ft_add_lexer_back(data->lst_lexer, command, PARENTHESIS);
	free(command);
	return (i);
}
