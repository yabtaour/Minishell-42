/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsaf <rsaf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 17:56:39 by yabtaour          #+#    #+#             */
/*   Updated: 2022/07/28 15:20:31 by rsaf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_this(t_env *env_clone)
{
	free(env_clone->name);
	free(env_clone->value);
	free(env_clone);
}

int	unset(t_data *data, t_cmd *lst_cmd)
{
	int		idx;
	t_env	*env_clone;
	t_env	*tmp;

	idx = 1;
	env_clone = data->lst_env;
	if (!lst_cmd->cmd[1])
		return (1);
	while (env_clone)
	{
		if (ft_strcmp(lst_cmd->cmd[idx], env_clone->name) == 0)
		{
			if (env_clone->next)
				env_clone->next->prev = env_clone->prev;
			if (env_clone->prev)
				env_clone->prev->next = env_clone->next;
			idx++;
			if (!lst_cmd->cmd[idx])
				return (0);
		}
		if (env_clone)
			env_clone = env_clone->next;
	}
	return (0);
}
