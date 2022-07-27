/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_fork_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabtaour <yabtaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:23:14 by rsaf              #+#    #+#             */
/*   Updated: 2022/07/27 14:23:40 by yabtaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_x(t_data *data, t_cmd *cmd)
{
	if (cmd->prev)
		data->general.index += cmd->prev->her_doc_num;
	return (data->general.index);
}

int	non_fork_funcs(t_data *data, t_cmd *cmd, int **pip)
{
	if (cmd->her_doc_num > 0 && ft_herdoc(data, cmd, pip, ft_x(data, cmd)) == 1)
	{
		if (cmd->her_in != 1)
			close(cmd->her_in);
		return (-666);
	}
	if (cmd->cmd && cmd->cmd[0])
	{
		if (ft_strcmp(cmd->cmd[0], "cd") == 0)
			data->error = cd(data, cmd);
		else if (ft_strcmp(cmd->cmd[0], "export") == 0 && !cmd->next)
			data->error = export(data, cmd, 1);
		else if (ft_strcmp(cmd->cmd[0], "env") == 0 && !cmd->next)
			data->error = ft_env_built(data, cmd->fd_out);
		else if(!ft_strcmp(cmd->cmd[0], "unset") && !cmd->next)
			data->error = unset(data, cmd);
		else if (ft_strcmp(cmd->cmd[0], "exit") == 0 && !cmd->next)
		{
			data->error = ft_exit(data, cmd, 1);
			if (data->error != 1)
				exit (data->error);
		}
		else
			return (-666);
	}
	return (data->error);
}
