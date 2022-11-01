/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_back.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:27:12 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/25 14:48:31 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	go_back_minus(t_data *data)
{
	int		exit_stat;
	char	*oldpwd;

	oldpwd = custom_getenv("OLDPWD", data->lst_env);
	exit_stat = chdir(oldpwd);
	if (exit_stat)
	{
		free(oldpwd);
		oldpwd = NULL;
		return (ft_putstr_fd("OLDPWD not set\n", 2), 1);
	}
	printf("%s\n", getenv("OLDPWD"));
	free(oldpwd);
	oldpwd = NULL;
	return (exit_stat);
}

void	print_error(void)
{
	printf("cd: error retrieving current directory:");
	printf("getcwd:cannot access parent directories:");
	printf(" No such file or directory\n");
}

int	go_home(t_data *data, char *cwd)
{
	int		exit_stat;
	char	*home;

	home = custom_getenv("HOME", data->lst_env);
	exit_stat = chdir(home);
	if (exit_stat)
	{
		free(cwd);
		free(home);
		cwd = NULL;
		home = NULL;
		ft_putstr_fd("HOME not set\n", 2);
		return (1);
	}
	update_pwd(data, cwd);
	free(cwd);
	free(home);
	home = NULL;
	cwd = NULL;
	return (exit_stat);
}
