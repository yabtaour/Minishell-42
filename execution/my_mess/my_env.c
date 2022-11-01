/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 11:42:22 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/09/21 18:16:56 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	my_env(t_data *data, t_cmd *lst_cmd)
{
	char	**cmd;
	t_env	*env;

	cmd = lst_cmd->cmd;
	env = data->lst_env;
	if (cmd[1])
	{
		printf("env: %s: No such file or directory\n", cmd[1]);
		return (127);
	}
	if (data->lst_env)
	{
		while (env)
		{
			if (env->value)
				printf("%s=%s\n", env->name, env->value);
			env = env->next;
		}
	}
	return (0);
}
