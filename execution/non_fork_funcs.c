/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_fork_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsaf <rsaf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:23:14 by rsaf              #+#    #+#             */
/*   Updated: 2022/07/28 15:02:28 by rsaf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_x(t_data *data, t_cmd *cmd)
{
	if (cmd->prev)
		data->general.index += cmd->prev->her_doc_num;
	return (data->general.index);
}

int	built_list(t_data *data, t_cmd *cmd)
{
	if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		data->error = cd(data, cmd);
	else if (ft_strcmp(cmd->cmd[0], "export") == 0 && !cmd->next)
		data->error = export(data, cmd, 1);
	else if (ft_strcmp(cmd->cmd[0], "env") == 0 && !cmd->next)
		data->error = ft_env_built(data, cmd->fd_out);
	else if (!ft_strcmp(cmd->cmd[0], "unset") && !cmd->next)
		data->error = unset(data, cmd);
	else if (ft_strcmp(cmd->cmd[0], "exit") == 0 && !cmd->next)
	{
		data->error = ft_exit(data, cmd, 1);
		if (data->error != 1)
			exit(data->error);
	}
	else
		return (-666);
	return (data->error);
}

int	non_fork_funcs(t_data *data, t_cmd *cmd, int **pip)
{
	if (cmd->her_doc_num > 0 && ft_herdoc(data, cmd, pip, ft_x(data, cmd)) == 1)
	{
		if (cmd->her_in != 1)
			close(cmd->her_in);
		if (cmd->cmd[0])
			return (-666);
	}
	if (cmd->cmd && cmd->cmd[0])
		data->error = built_list(data, cmd);
	return (data->error);
}
