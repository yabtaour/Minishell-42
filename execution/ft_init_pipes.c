#include "../minishell.h"

int	**ft_init_pipes(t_data *data, t_cmd *lst_cmd, int lent)
{
	int	idx;
	int **pip;
	int	old_input;
	int	old_output;
	t_cmd *cmd_clone;

	if (lst_cmd)
	{
		pip = malloc((lent - 1) * sizeof(int*));
		for (int i = 0; i < lent - 1; i++)
			pip[i] = malloc(2 * sizeof(int));
		cmd_clone = lst_cmd;
		idx = 0;
		while (idx < lent - 1)
		{
			pipe(pip[idx]);
			idx++;
		}
		idx = 0;
		while (cmd_clone)
		{
			old_input = cmd_clone->fd_in;
			old_output = cmd_clone->fd_out;
			if (idx == 0 && !cmd_clone->next)
			{
				cmd_clone->fd_in = 0;
				cmd_clone->fd_out = 1;
			}
			else if (idx == 0 && cmd_clone->next)
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
			if (old_input != 0)
				cmd_clone->fd_in = old_input;
			if (old_output != 1)
				cmd_clone->fd_out = old_output;
			cmd_clone = cmd_clone->next;
			idx++;
		}
	}
	return (pip);
}