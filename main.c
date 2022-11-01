/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:29:59 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/10/07 10:23:02 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_initialize1(t_data *data, int argc, char **env)
{
	data->ac = argc;
	data->first_export = NULL;
	data->general.old_error = 0;
	data->general.index = 0;
	if (env && env[0])
		data->env = env;
	else
	{
		data->env = malloc (sizeof(char *) * 4);
		data->env[0] = ft_strdup("SHLVL=1");
		data->env[1] = ft_strdup("PWD=/Users/ssabbaji/Desktop/workingms");
		data->env[2] = ft_strdup("_=./minishell");
		data->env[3] = NULL;
	}
	ft_env(data);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argv;
	if (!ft_initialize1(&data, argc, env))
		exit(1);
	if (!ft_sub_main(&data))
		return (0);
}
