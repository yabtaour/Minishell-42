/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 10:39:20 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/10/03 15:29:52 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_statushandling(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3)
			write(2, "Quit: 3\n", 8);
		if (WTERMSIG(status) == 2)
			write(2, "\n", 1);
		return (128 + WTERMSIG(status));
	}
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	terminate_pid(pid_t lastchild)
{
	int	status;

	waitpid(lastchild, &status, 0);
	while (wait(NULL) != -1)
		;
	return (ft_statushandling(status));
}

int	check_path(t_env *lst_env)
{
	while (lst_env && lst_env->name)
	{
		if (!ft_strcmp(lst_env->name, "PATH"))
			return (1);
		lst_env = lst_env->next;
	}
	return (0);
}
