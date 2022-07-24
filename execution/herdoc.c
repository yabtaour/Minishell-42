#include "../minishell.h"

// herdoc can output to the cmd like wc
// in bash herdoc do not output to a file just created
// the herdoc before the syntax error

int	*init_herdoc_out(t_cmd *cmd_lst)
{
	t_cmd *cmd_clone;
	int	*pip;

	cmd_clone = cmd_lst;
	while (cmd_clone)
	{
		// if (cmd_clone->her_doc_num > 0 &&)
		cmd_clone = cmd_clone->next;
	}
	pip = malloc(sizeof(int *) * 2);
	pipe(pip);
	if (cmd_lst->cmd[0] && !cmd_lst->next)
		cmd_lst->fd_in = pip[0];
	return (pip);
}

int	ft_herdoc(t_data *data, t_cmd *cmd_lst, int **pip)
{
	int		pid;
	int		fd_out;
	int		i;
	char	*buff;
	t_cmd	*cmd_clone;

	pid = -99;
	i = 0;
	fd_out = 0;
	cmd_clone = cmd_lst;
	pid = fork();
	if (data->her_doc && pid == 0)
	{
			while (1 && i < cmd_clone->her_doc_num)
			{
				buff = readline("heredoc> ");
				if (!buff)
					return (1);
				else if (buff[0] != '\0' && !strcmp(buff, data->eof[i]))
					i++;
				else if (i >= cmd_clone->her_doc_num)
					break ;
				else
				{
					ft_putstr_fd(buff, cmd_clone->her_in);
					ft_putstr_fd("\n", cmd_clone->her_in);
				}
			}
			close(cmd_clone->fd_in);
			close(cmd_clone->her_in);
			close_fds(cmd_clone);
			close_pipes(pip, data->general.lent);
			exit(0);
	}
	waitpid(pid, 0, 0);
	if (cmd_clone->her_in != 1)
		close(cmd_clone->her_in);
	return (1);
}
