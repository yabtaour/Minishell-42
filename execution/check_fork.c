/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:50:24 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/10/05 11:04:38 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_builtins(t_data *data, t_cmd *cmd_lst)
{
	char	**cmd;

	cmd = cmd_lst->cmd;
	if (!ft_strcmp(cmd[0], "export"))
		g_vars.g_exit_stat = export(data, cmd_lst);
	else if (!ft_strcmp(cmd[0], "unset"))
		g_vars.g_exit_stat = unset(data, cmd_lst);
	else if (!ft_strcmp(cmd[0], "echo"))
		g_vars.g_exit_stat = my_echo(cmd_lst);
	else if (!ft_strcmp(cmd[0], "pwd"))
		g_vars.g_exit_stat = my_pwd(data, data->lst_cmd);
	else if (!ft_strcmp(cmd[0], "env"))
		my_env(data, data->lst_cmd);
	else if (!ft_strcmp(cmd[0], "exit"))
		g_vars.g_exit_stat = my_exit(cmd_lst, data->general.old_error);
	else
		return (NO_BUILT);
	return (g_vars.g_exit_stat);
}

int	nofork_list(t_data *data, t_cmd *cmd)
{
	data->fork_flag = 0;
	if (!ft_strcmp(cmd->cmd[0], "cd") && !cmd->next)
		g_vars.g_exit_stat = my_cd(data, cmd);
	else if (!ft_strcmp(cmd->cmd[0], "export") && !cmd->next)
		g_vars.g_exit_stat = export(data, cmd);
	else if ((!ft_strcmp(cmd->cmd[0], "env")) && !cmd->next)
		my_env(data, cmd);
	else if (!ft_strcmp(cmd->cmd[0], "unset") && !cmd->next)
		g_vars.g_exit_stat = unset(data, cmd);
	else if (!ft_strcmp(cmd->cmd[0], "exit") && !cmd->next)
	{
		if (cmd->prev)
			return (0);
		g_vars.g_exit_stat = my_exit(cmd, data->general.old_error);
	}
	else
		data->fork_flag = 1;
	return (g_vars.g_exit_stat);
}

int	check_nonfork(t_data *data, t_cmd *cmd)
{
	int	idx;

	idx = check_delim_idx(data, cmd);
	data->fork_flag = 0;
	if (cmd->her_doc_num && heredoc_exec(data, cmd, idx))
	{
		if (cmd->her_in != 1)
			close(cmd->her_in);
		if (cmd->cmd[0])
			data->fork_flag = 1;
	}
	if (cmd->cmd && cmd->cmd[0])
		return (nofork_list(data, cmd));
	return (g_vars.g_exit_stat);
}

int	check_fork(int *pid, t_data *data)
{
	int	i;

	i = 0;
	if (*pid != 0 && data->fork_flag)
	{
		*pid = fork();
		if (*pid < 0)
		{
			perror("fork() error");
			exit(1);
		}
		i++;
	}
	return (i);
}
