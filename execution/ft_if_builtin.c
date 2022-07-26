/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_if_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsaf <rsaf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:23:04 by rsaf              #+#    #+#             */
/*   Updated: 2022/07/26 12:23:05 by rsaf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_if_builtin(t_data *data, t_cmd *lst_cmd)
{
	if (ft_strcmp(lst_cmd->cmd[0], "echo") == 0)
		data->error = echo(data, lst_cmd, 1);
	else if (ft_strcmp(lst_cmd->cmd[0], "pwd") == 0)
		data->error = pwd(data, lst_cmd, 1);
	else if (ft_strcmp(lst_cmd->cmd[0], "unset") == 0)
		data->error = unset(data, lst_cmd);
	else if (ft_strcmp(lst_cmd->cmd[0], "export") == 0)
		data->error = export(data, lst_cmd, 1);
	else if (ft_strcmp(lst_cmd->cmd[0], "env") == 0)
		ft_print_env(data->lst_env, 0, 1);
	else
		return (2);
	exit (data->error);
}
