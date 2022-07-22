#include "../minishell.h"

// herdoc can output to the cmd like wc
// in bash herdoc do not output to a file just created
// the herdoc before the syntax error

int ft_herdoc(t_data *data)
{
	int		pip[2];
	int     i = 0;
	t_cmd   *cmd_clone = data->lst_cmd;
	char	*buff;

	pipe(pip);
	if (data->her_doc)
	{
		while (69 && i < data->her_doc)
		{
			buff = readline("-> ");
			if (!buff)
				return (0);
			else if (buff[0] != '\0' && !strcmp(buff, data->eof[i]))
				i++;
			else if (i >= data->her_doc)
				return (0);
			else
			{
				ft_putstr_fd(buff, pip[1]);
				ft_putstr_fd("\n", pip[1]);
			}
		}
	}
	return (0);
}