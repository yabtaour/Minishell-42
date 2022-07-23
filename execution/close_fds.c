#include "../minishell.h"

int	close_fds(t_cmd *lst_cmd)
{
	t_cmd	*cmd_clone;

	cmd_clone = lst_cmd;
	while (cmd_clone)
	{
		if (cmd_clone->fd_in != 0)
			close(cmd_clone->fd_in);
		if (cmd_clone->fd_out != 1)
			close(cmd_clone->fd_out);
		cmd_clone = cmd_clone->next;
	}
	return (0);
}
