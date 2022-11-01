/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 10:52:05 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/30 16:01:04 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	display_error(char *cmd)
{
	printf("bash: exit: %s :numeric argument required\n", cmd);
	return (255);
}

int	ft_isdigit(char *num)
{
	int	i;

	i = 0;
	while (num[i])
	{
		if (num[i] >= '0' && num[i] <= '9')
			return (1);
		i++;
	}
	return (0);
}

long long	ft_atoi_long(char *str)
{
	int			i;
	int			n;
	long long	res;

	i = 0;
	res = 0;
	n = 1;
	while (str[i] <= 32)
		i++;
	if (str[i] == '-')
		n = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - '0';
		if (res < 0)
			return (display_error(str));
		i++;
	}
	return (res * n);
}

int	my_exit(t_cmd *lst_cmd, int old_error)
{
	char	**cmd;
	int		exit_stat;

	exit_stat = g_vars.g_exit_stat;
	cmd = lst_cmd->cmd;
	printf("exit\n");
	if (cmd[1])
	{
		if (cmd[2])
			return (printf("bash: exit: too many arguments\n"), 1);
		else if (ft_isdigit(cmd[1]))
			exit_stat = ft_atoi_long(cmd[1]);
		else
			display_error(cmd[1]);
	}
	else
		exit(old_error);
	exit((unsigned char)exit_stat);
}
