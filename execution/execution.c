/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 18:53:10 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/10/07 13:18:48 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	dup_and_close(t_data *data, t_cmd *cmd)
{
	dup2(cmd->fd_in, 0);
	dup2(cmd->fd_out, 1);
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	if (cmd->fd_out != 1)
		close(cmd->fd_out);
	close_fds(cmd);
	close_pipes(data->pipes, data->general.count);
	g_vars.g_exit_stat = check_builtins(data, cmd);
	if (g_vars.g_exit_stat == NO_BUILT)
		g_vars.g_exit_stat = execution_2(data, cmd);
	return (g_vars.g_exit_stat);
}

int	execution(t_data *data, t_cmd *cmd)
{
	int		pid;
	int		fork_c;

	fork_c = 0;
	pid = 1;
	while (cmd)
	{
		g_vars.g_exit_stat = check_nonfork(data, cmd);
		if (g_vars.g_heredoc == 0)
			return (HEREDOC_EXE);
		fork_c += check_fork(&pid, data);
		signal(SIGINT, SIG_IGN);
		if (pid == 0 && cmd->fd_in != -69)
		{
			signal(SIGINT, SIG_DFL);
			g_vars.g_where_ami = 0;
			g_vars.g_exit_stat = dup_and_close(data, cmd);
			exit(g_vars.g_exit_stat);
		}
		cmd = cmd->next;
	}
	close_all(cmd, data->pipes, data->general.count);
	if (fork_c)
		g_vars.g_exit_stat = terminate_pid(pid);
	return (g_vars.g_exit_stat);
}

int	pre_execution(t_data *data)
{
	t_cmd	*cmd;
	int		pid;

	pid = 0;
	data->general.count = c_lstcmd(data);
	if (data->lst_cmd)
	{
		cmd = data->lst_cmd;
		data->pipes = initialize_pipes(data);
		if (execution(data, cmd) == HEREDOC_EXE)
			g_vars.g_exit_stat = 1;
	}
	return (0);
}
