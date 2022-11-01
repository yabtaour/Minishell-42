/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 11:02:55 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/10/03 15:01:48 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	close_all(t_cmd *lst_cmd, int **pipes, int count)
{
	int		idx;
	t_cmd	*cmd;

	idx = 0;
	cmd = lst_cmd;
	while (cmd)
	{
		if (cmd->fd_in != 0)
			close(cmd->fd_in);
		if (cmd->fd_out != 1)
			close(cmd->fd_out);
		cmd = cmd->next;
	}
	while (idx < count - 1)
	{
		close(pipes[idx][1]);
		close(pipes[idx][0]);
		idx++;
	}
	idx = 0;
	while (idx < count - 1)
		free(pipes[idx++]);
	free(pipes);
	return (0);
}

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

int	close_pipes(int **pip, int lent)
{
	int	idx;

	idx = 0;
	while (idx < lent - 1)
	{
		close(pip[idx][1]);
		close(pip[idx][0]);
		idx++;
	}
	idx = 0;
	while (idx < lent - 1)
		free(pip[idx++]);
	free(pip);
	return (0);
}
