 #include "../minishell.h"

int	ft_add_redirection(t_data *data, int i)
{
	char	*command = NULL;
	int		len;
	int		origin;

	origin = i;
	while (data->cmd[i] && ft_is_redirection(data->cmd[i]))
	{
		i++;
		len++;
	}
	command = malloc(sizeof(char) * len + 1);
	len = 0;
	while (data->cmd[origin] && ft_is_redirection(data->cmd[origin]))
	{
		command[len] = data->cmd[origin];
		len++;
		origin++;
	}
	command[len] = '\0';
	data->lst_lexer = ft_add_lexer_back(data->lst_lexer, command, REDIRECTION);
	free(command);
	return (i);
}