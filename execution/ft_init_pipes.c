#include "../minishell.h"

int	**ft_allocat_pipes(int lent, int i, int idx)
{
	int	**pip;

	pip = malloc((lent - 1) * sizeof(int *));
	while (i < lent - 1)
	{
		pip[i] = malloc(2 * sizeof(int));
		i++;
	}
	while (idx < lent - 1)
	{
		pipe(pip[idx]);
		idx++;
	}	
	return (pip);
}

void	check_for_redfd(t_cmd *cmd_clone, int old_input, int old_output)
{
	if (old_input != 0)
		cmd_clone->fd_in = old_input;
	if (old_output != 1)
		cmd_clone->fd_out = old_output;
}

int	**ft_init_pipes(t_data *data, int lent, int idx)
{
	int		**pip;
	int		old_input;
	int		old_output;
	t_cmd	*cmd_clone;

	if (data->lst_cmd)
	{
		cmd_clone = data->lst_cmd;
		idx = 0;
		pip = ft_allocat_pipes(lent, 0, idx);
		while (cmd_clone)
		{
			old_input = cmd_clone->fd_in;
			old_output = cmd_clone->fd_out;
			if (idx == 0 && cmd_clone->next)
			{
				cmd_clone->fd_in = 0;
				cmd_clone->fd_out = pip[idx][1];
			}
			else if (idx != 0 && cmd_clone->next)
			{
				cmd_clone->fd_in = pip[idx - 1][0];
				cmd_clone->fd_out = pip[idx][1];
			}
			else if (idx != 0 && !cmd_clone->next)
			{
				cmd_clone->fd_in = pip[idx - 1][0];
				cmd_clone->fd_out = 1;
			}
			check_for_redfd(cmd_clone, old_input, old_output);
			cmd_clone = cmd_clone->next;
			idx++;
		}
	}
	return (pip);
}
