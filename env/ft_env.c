/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:16:16 by yabtaour          #+#    #+#             */
/*   Updated: 2022/09/21 16:10:39 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_create_my_env(t_data *data)
{
	char	*value;

	value = "PWD=/Users/ssabbaji/Desktop/minishell_2";
	data->env = malloc (sizeof(char *) * 4);
	if (!data->env)
		exit(1);
	data->env[0] = ft_substr(value, 0, ft_strlen(value));
	value = "SHLVL=1";
	data->env[1] = ft_substr(value, 0, ft_strlen(value));
	value = "_=/usr/bin/env";
	data->env[2] = ft_substr(value, 0, ft_strlen(value));
	data->env[3] = NULL;
}

void	ft_create_env_list(t_env **envi, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		*envi = ft_add_to_env_back(*envi, env[i]);
		i++;
	}
}

void	ft_env(t_data *data)
{
	if (data->env)
		ft_create_env_list(&data->lst_env, data->env);
}
