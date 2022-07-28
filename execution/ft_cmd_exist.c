/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_exist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsaf <rsaf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:22:51 by rsaf              #+#    #+#             */
/*   Updated: 2022/07/28 13:47:27 by rsaf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// this func check if the cmd is exist or not
// right now for testing if the cmd do 
// not exist it return a messg with NULL
// if cmd exist it get exuxte

int	check_result(int found, t_data *data)
{
	if (found == 1)
		return (1);
	else
	{
		ft_putstr_fd("mshell: command not found\n", 2);
		data->error = 127;
		exit(127);
	}
	return (0);
}

char	*if_no_path(t_data *data, t_cmd *cmd_lst)
{
	char	*path;

	path = NULL;
	path = ft_strjoin(path, ".");
	path = ft_strjoin(path, cmd_lst->cmd[0]);
	if (access(path, F_OK) != 0)
		return (printf("mshell: command not found.\n"), NULL);
	return (path);
}

int	slash_dot(t_cmd *lst_cmd)
{
	if (lst_cmd->cmd[0][0] == '.' || lst_cmd->cmd[0][0] == '/')
		return (1);
	else
		return (0);
}

char	*ft_cmd_exist(t_data *data, t_cmd *lst_cmd, int idx)
{
	int		cmd_nb;
	char	*path;
	int		found;

	found = 0;
	path = NULL;
	if (ft_get_env(data, "PATH") == NULL && lst_cmd->cmd[0][0] != '/')
		return (lst_cmd->cmd[0]);
	if (slash_dot(lst_cmd))
		return (data->lst_cmd->cmd[0]);
	while (data->paths[++idx] && found == 0)
	{
		path = ft_strjoin(data->paths[idx], "/");
		path = ft_strjoin(path, lst_cmd->cmd[0]);
		if (access(path, F_OK) == 0)
		{
			found = 1;
			break ;
		}
		free(path);
	}
	if (check_result(found, data) == 1)
		return (path);
	return (NULL);
}
