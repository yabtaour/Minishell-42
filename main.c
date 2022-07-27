/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabtaour <yabtaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:29:08 by rsaf              #+#    #+#             */
/*   Updated: 2022/07/27 17:24:34 by yabtaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_create_my_env(t_data *data)
{
	char	*value;

	value = "PWD=/Users/yabtaour/Desktop/my_minishell";
	data->env = malloc (sizeof(char *) * 4);
	data->env[0] = ft_substr(value, 0, ft_strlen(value));
	value = "SHLVL=1";
	data->env[1] = ft_substr(value, 0, ft_strlen(value));
	value = "_=/usr/bin/env";
	data->env[2] = ft_substr(value, 0, ft_strlen(value));
	data->env[3] = NULL;
}

void	ft_initialize1(t_data *data, int argc, char **env)
{
	data->ac = argc;
	data->first_export = NULL;
	data->general.old_error = 0;
	if (env[0])
		data->env = env;
	else
		ft_create_my_env(data);
	ft_env(data);
}

void	ft_initialize2(t_data *data)
{
	data->lst_cmd = NULL;
	data->lst_lexer = NULL;
	data->error = 0;
	data->her_doc = 0;
	data->general.index = 0;
	// rl_catch_signals = 0;
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}

void	ft_free_norme(t_data *data)
{
	free_split(data->eof);
	ft_free_lexer(data->lst_lexer);
	ft_free_cmd(data->lst_cmd);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	ft_initialize1(&data, argc, env);
	while (69)
	{
		g_where_ami = 1;
		ft_initialize2(&data);
		data.cmd = readline("minishell-1.0> ");
		if (!data.cmd)
			break ;
		if (data.cmd && data.cmd[0] != '\0')
		{
			ft_lexer(&data);
			data.error = ft_syntax_analyzer(&data);
			if (data.error)
			{
				ft_free_lexer(data.lst_lexer);
				data.general.old_error = data.error;
				continue ;
			}
			ft_expanding(&data);
			ft_parsing(&data);
			execution(&data);
			ft_free_norme(&data);
		}
		data.general.old_error = data.error;
	}
	return (0);
}
