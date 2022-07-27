/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabtaour <yabtaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 17:56:35 by yabtaour          #+#    #+#             */
/*   Updated: 2022/07/27 17:56:36 by yabtaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env_built(t_data *data, int fd)
{
	t_env	*env_clone;

	env_clone = data->lst_env;
	if (env_clone)
	{
		while (env_clone)
		{
			if (env_clone->value && ft_strlen(env_clone->value))
			{
				ft_putstr_fd(env_clone->name, fd);
				ft_putstr_fd("=", fd);
				ft_putstr_fd(env_clone->value, fd);
				ft_putstr_fd("\n", fd);
			}
			env_clone = env_clone->next;
		}
	}
	return (0);
}
