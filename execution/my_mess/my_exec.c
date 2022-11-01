/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 11:10:11 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/10/03 15:31:22 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*generate_path(t_data *data, char **cmd, int i, int flag)
{
	char	*path;

	path = NULL;
	if (!flag)
	{
		path = ft_strjoin(data->paths[i], "/");
		path = ft_strjoin(path, cmd[0]);
	}
	else if (flag == 1)
		path = ft_strjoin(path, cmd[0]);
	else
	{
		path = ft_strjoin(custom_getenv("PWD", data->lst_env), "/");
		path = ft_strjoin(path, cmd[0]);
	}
	return (path);
}

int	check_access(t_data *data, char **cmd, int i, int flag)
{
	char	*path;
	int		fd;
	int		size;

	size = 0;
	fd = 0;
	path = NULL;
	path = generate_path(data, cmd, i, flag);
	fd = access(path, F_OK | X_OK);
	size = count_cmds(cmd);
	cmd[size] = NULL;
	if (fd == -1)
		return (0);
	else
	{
		if (data->lst_cmd->fd_in != 0)
			close(data->lst_cmd->fd_in);
		if (data->lst_cmd->fd_out != 1)
			close(data->lst_cmd->fd_out);
		execve(path, cmd, data->env);
		perror("execve() error");
	}
	free(path);
	return (1);
}

void	print_cmd_error(char *cmd, int flag)
{
	if (flag)
	{
		ft_putstr_fd("bash :", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else
	{
		ft_putstr_fd("bash :", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}

int	check_nonabs(t_data *data, char **cmd)
{
	int	ret;
	int	i;

	i = -1;
	ret = 0;
	if (check_path(data->lst_env))
	{
		data->paths = ft_split(custom_getenv("PATH", data->lst_env), ':');
		while (data->paths[++i] && ret != 1)
			ret = check_access(data, cmd, i, 0);
		if (!ret)
		{
			print_cmd_error(cmd[0], 1);
			return (0);
		}
	}
	else if (!check_access(data, cmd, 0, 3))
	{
		print_cmd_error(cmd[0], 0);
		return (0);
	}
	return (1);
}

int	execution_2(t_data *data, t_cmd *lst_cmd)
{
	char	**cmd;

	data->paths = NULL;
	cmd = lst_cmd->cmd;
	if (cmd[0][0] == '/' || cmd[0][0] == '.')
		check_access(data, cmd, 0, 1);
	if (check_nonabs(data, cmd))
		g_vars.g_exit_stat = 0;
	else
		g_vars.g_exit_stat = 127;
	return (g_vars.g_exit_stat);
}
