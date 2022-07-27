#include "../minishell.h"

int	ft_flag_echo(t_cmd *cmd_clone, int flag, int idx, int x)
{
	if (cmd_clone->cmd[idx][x] == 'n' && flag != 0)
		flag = 1;
	else if (cmd_clone->cmd[idx][x] != 'n')
		flag = 0;
	return (flag);
}

int	check_opt(t_cmd *cmd_lst, int x, int idx, int flag)
{
	int		write_from;
	t_cmd	cmd_clone;

	if (cmd_lst)
	{
		write_from = 0;
		cmd_clone = *cmd_lst;
		while (cmd_clone.cmd[idx])
		{
			x = 0;
			flag = -1;
			while (cmd_clone.cmd[idx][++x] && cmd_clone.cmd[idx][0] == '-')
				flag = ft_flag_echo(&cmd_clone, flag, idx, x);
			if (flag == 1)
				write_from = idx;
			if (flag == 0 || cmd_clone.cmd[1][0] != '-')
				return (idx - 1);
			idx++;
		}
		return (write_from);
	}
	return (1);
}

int	echo(t_data *data, t_cmd *cmd_lst, int fd)
{
	int	nl;
	int	write_from;

	if (data && cmd_lst && cmd_lst->cmd[0])
	{
		nl = 0;
		write_from = 1;
		write_from += check_opt(cmd_lst, 0, 1, -1);
		if (write_from > 1)
			nl = 1;
		while (cmd_lst->cmd[write_from])
		{
			ft_putstr_fd(cmd_lst->cmd[write_from], fd);
			if (cmd_lst->cmd[write_from + 1])
				ft_putstr_fd(" ", fd);
			write_from++;
		}
		if (nl == 0)
			write(fd, "\n", 1);
		return (0);
	}
	return (1);
}
