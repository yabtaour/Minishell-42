#include "../minishell.h"

int	ft_add_word(t_data *data, int i)
{
	int		len = 0;
	char	c;
	int		origin;
	char	*command = NULL;
	int		flag_s = 0;
	int		flag_d = 0;

	origin = i;
	while (data->cmd[i] && ft_is_word(data->cmd[i]))
	{
		if (data->cmd[i] == '"' || data->cmd[i] == '\'')
		{
			c = data->cmd[i];
			i++;
			len++;
			while (data->cmd[i] && data->cmd[i] != c)
			{
				i++;
				len++;
			}
		}
		len++;
		i++;
	}
	command = malloc (sizeof(char) * len + 1);
	len = 0;
	while (data->cmd[origin] && ft_is_word(data->cmd[origin]))
	{
		if (data->cmd[origin] == '"' || data->cmd[origin] == '\'')
		{
			c = data->cmd[origin];
			command[len] = data->cmd[origin];
			origin++;
			len++;
			while (data->cmd[origin] && data->cmd[origin] != c)
			{
				command[len] = data->cmd[origin];
				origin++;
				len++;
			}
		}
		command[len] = data->cmd[origin];
		len++;
		origin++;
	}
	command[len] = '\0';
	data->lst_lexer = ft_add_lexer_back(data->lst_lexer, command, WORD);
	ft_print_lexer(data->lst_lexer);
	free(command);
	return (i);
}