#include "../minishell.h"

int	ft_add_semi(t_data *data, int i)
{
	int		origin = i;
	int		len = 0;
	char	*command = NULL;

	while (data->cmd[i] && data->cmd[i] == ';')
	{
		i++;
		len++;
	}
	command = malloc(sizeof(char) * len + 1);
	len = 0;
	while (data->cmd[origin] && data->cmd[origin] == ';')
	{
		command[len] = data->cmd[origin];
		len++;
		origin++;
	}
	command[len] = '\0';
	data->lst_lexer = ft_add_lexer_back(data->lst_lexer, command, SEMI);
	free(command);
	return (i);
}
