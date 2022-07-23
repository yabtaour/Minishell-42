#include "../minishell.h"

// herdoc can output to the cmd like wc
// in bash herdoc do not output to a file just created
// the herdoc before the syntax error

int	*init_herdoc_out(t_cmd *cmd_lst)
{
	int	*pip;

	pip = malloc(sizeof(int *) * 2);
	pipe(pip);
	if (cmd_lst->cmd[0] && !cmd_lst->next)
		cmd_lst->fd_in = pip[0];
	return (pip);
}

int	ft_herdoc(t_data *data)
{
	int		fd_out;
	int		*pip;
	int		i;
	char	*buff;
	t_cmd	*cmd_clone;

	i = 0;
	fd_out = 0;
	cmd_clone = data->lst_cmd;
	if (data->her_doc)
	{
		pip = init_herdoc_out(cmd_clone);
		while (69 && i < data->her_doc)
		{
			buff = readline("heredoc> ");
			if (!buff)
				return (1);
			else if (buff[0] != '\0' && !strcmp(buff, data->eof[i]))
				i++;
			else if (i >= data->her_doc)
				return (1);
			else
			{
				ft_putstr_fd(buff, pip[1]);
				ft_putstr_fd("\n", pip[1]);
			}
		}
		close(pip[0]);
		close(pip[1]);
		if (cmd_clone->fd_out != 1)
			close(cmd_clone->fd_out);
		if (cmd_clone->fd_in != 0)
			close(cmd_clone->fd_in);
	}
	HERE
	return (1);
}
