/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_fork_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsaf <rsaf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:23:14 by rsaf              #+#    #+#             */
/*   Updated: 2022/07/26 12:23:15 by rsaf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_idx(t_data *data, t_cmd *cmd)
{
	if (cmd->prev)
		data->general.index += cmd->prev->her_doc_num;
	return (data->general.index);
}

int	non_fork_funcs(t_data *data, t_cmd *cmd, int **pip)
{
	if (cmd->her_doc_num > 0 && ft_herdoc(data, cmd, pip , find_idx(data, cmd)) == 1)
	{
		if (cmd->her_in != 1)
			close(cmd->her_in);
		return (1);
	}
	if (cmd->cmd && cmd->cmd[0])
	{
		if (strcmp(cmd->cmd[0], "cd") == 0)
			data->error = cd(data, cmd);
		else if (strcmp(cmd->cmd[0], "export") == 0 && !cmd->next)
			data->error = export(data, cmd, 1);
		else if (strcmp(cmd->cmd[0], "env") == 0 && !cmd->next)
			ft_env_built(data);
		else
			return (-666);
	}
	return (data->error);
}
