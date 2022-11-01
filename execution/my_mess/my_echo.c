/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 10:42:26 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/30 16:52:10 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_rest(char **cmd, int i, int flag)
{
	char	*echo;
	char	*free_echo;

	if (flag)
	{
		echo = join_cmd(cmd, count_cmds(cmd), i);
		free_echo = echo;
		echo = ft_substr(echo, 0, ft_strlen(echo) - 1);
		printf("%s", echo);
		printf("\n");
	}
	if (!flag)
	{
		echo = join_cmd(cmd, count_cmds(cmd), i);
		free_echo = echo;
		echo = ft_substr(echo, 0, ft_strlen(echo) - 1);
		printf("%s", echo);
	}
	free(free_echo);
}

int	start_index(char **cmd)
{
	int	idx;
	int	i;

	i = 1;
	idx = 0;
	while (cmd[i])
	{
		if (!check_valid(cmd[i]))
			return (i);
		i++;
	}
	return (0);
}

int	my_echo(t_cmd *cmd_lst)
{
	char	**cmd;
	int		idx;

	idx = 0;
	cmd = cmd_lst->cmd;
	if (!cmd[1])
		write(1, "\n", 1);
	idx = start_index(cmd);
	if (!idx)
		return (0);
	if (idx == 1)
		print_rest(cmd, idx, 1);
	else
		print_rest(cmd, idx, 0);
	return (0);
}
