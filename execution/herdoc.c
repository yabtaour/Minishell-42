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
	ft_print_cmd(cmd_clone);
	if (data->her_doc)
	{
		while (69 && i < data->her_doc)
		{
			buff = readline("heredoc> ");
			if (!buff)
				return (0);
			else if (buff[0] != '\0' && !strcmp(buff, data->eof[i]))
				i++;
			else if (i >= data->her_doc)
				return (0);
			else
			{
				ft_putstr_fd(buff, cmd_clone->fd_out);
				ft_putstr_fd("\n", cmd_clone->fd_out);
			}
		}
		if (cmd_clone->fd_out != 1)
			close(cmd_clone->fd_in);
	}
	return (0);
}