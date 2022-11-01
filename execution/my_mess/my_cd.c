/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:42:55 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/10/07 12:31:00 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	my_chdir(t_data *data, char *cmd, char *cwd)
{
	char	*new_pwd;

	new_pwd = cmd;
	if (!ft_strcmp(cmd, "-"))
		return (go_back_minus(data));
	else
		g_vars.g_exit_stat = chdir(new_pwd);
	if (g_vars.g_exit_stat)
		return (perror("chdir() error:"), 1);
	else
	{
		new_pwd = getcwd(NULL, 256);
		update_env(data, "OLDPWD", cwd);
		update_env(data, "PWD", new_pwd);
	}
	free(new_pwd);
	return (g_vars.g_exit_stat);
}

void	find_dir(t_data *data, char *pwd, char *upd)
{
	int		i;
	char	*test_pwd;

	i = 0;
	test_pwd = NULL;
	while (pwd[i])
		i++;
	while (pwd[i] != '/')
		i--;
	test_pwd = ft_strncpy(test_pwd, pwd, i);
	if (chdir(test_pwd))
		find_dir(data, test_pwd, upd);
	else
		my_chdir(data, test_pwd, upd);
	free(test_pwd);
}

int	catch_error(t_data *data)
{
	char	*old_pwd;

	old_pwd = custom_getenv("PWD", data->lst_env);
	print_error();
	g_vars.g_exit_stat = go_home(data, old_pwd);
	return (g_vars.g_exit_stat);
}

int	my_cd(t_data *data, t_cmd *lst_cmd)
{
	char	*cwd;
	char	**cmd;
	int		exit_stat;

	cmd = lst_cmd->cmd;
	cwd = getcwd(NULL, 256);
	if (cmd[1])
	{
		if (!cwd)
			return (catch_error(data));
		else
			exit_stat = my_chdir(data, cmd[1], cwd);
	}
	else
		return (go_home(data, cwd));
	free(cwd);
	return (exit_stat);
}
