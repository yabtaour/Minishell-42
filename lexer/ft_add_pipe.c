#include "../minishell.h"

int	ft_add_pipe(t_data *data, int i)
{
	int		origin = i;
	char	*command = NULL;
	int		len = 0;

	while (data->cmd[i] && data->cmd[i] == '|')
	{
		i++;
		len++;
	}
	command = malloc (sizeof(char) * len + 1);
	len = 0;
	while (data->cmd[origin] && data->cmd[origin] == '|')
	{
		command[len] = data->cmd[origin];
		origin++;
		len++;
	}
	command[len] = '\0';
	data->lst_lexer = ft_add_lexer_back(data->lst_lexer, command, PIPE);
	free(command);
	return (i);
}