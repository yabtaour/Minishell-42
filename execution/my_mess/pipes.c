/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:12:33 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/15 17:25:33 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	**alloc_pipes(t_data *data)
{
	int	**fds;
	int	c;
	int	i;

	c = c_lstcmd(data);
	fds = malloc(sizeof(int *) * (c - 1));
	if (!fds)
		exit(1);
	i = 0;
	while (i < c - 1)
	{
		fds[i] = malloc(sizeof(int) * 2);
		if (!fds[i])
			exit(1);
		pipe(fds[i]);
		i++;
	}
	return (fds);
}

void	init_fd(int **fd, t_cmd *cmd, int i)
{
	if (i == 0 && cmd->next)
	{
		if (cmd->fd_out == 1)
			cmd->fd_out = fd[i][1];
	}
	else if (i != 0 && cmd->next)
	{
		if (cmd->fd_in == 0)
			cmd->fd_in = fd[i - 1][0];
		if (cmd->fd_out == 1)
			cmd->fd_out = fd[i][1];
	}
	else if (i != 0 && !cmd->next)
		if (cmd->fd_in == 0)
			cmd->fd_in = fd[i - 1][0];
}

int	**initialize_pipes(t_data *data)
{
	int		i;
	int		**fd;
	t_cmd	*cmd;

	i = 0;
	cmd = data->lst_cmd;
	fd = alloc_pipes(data);
	if (!fd)
		exit(1);
	while (cmd)
	{
		init_fd(fd, cmd, i);
		i++;
		cmd = cmd->next;
	}
	return (fd);
}
