/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabtaour <yabtaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:29:08 by rsaf              #+#    #+#             */
/*   Updated: 2022/07/27 00:28:13 by yabtaour         ###   ########.fr       */
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

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	data.ac = argc;
	data.av = argv;
	if (env[0])
		data.env = env;
	else
		ft_create_my_env(&data);
	ft_env(&data);
	data.first_export = NULL;
	data.general.old_error = 0;
	while (69)
	{
		g_where_ami = 1;
		data.lst_lexer = NULL;
		data.lst_cmd = NULL;
		data.error = 0;
		data.her_doc = 0;
		// rl_catch_signals = 0;
    	signal(SIGINT, handler);
		signal(SIGQUIT, handler);
		data.cmd = readline("minishell-1.0 > ");
		if (!data.cmd || !ft_strcmp(data.cmd, "exit"))
		{
			if (data.cmd)
			{
				printf("exit\n");
				return (0);
			}
			break;
		}
		data.general.index = 0;
		if (data.cmd && data.cmd[0] != '\0')
		{
			data.cmd = ft_strtrim(data.cmd, " ");
			add_history(data.cmd);
			ft_lexer(&data);
			free(data.cmd);
			data.error = ft_syntax_analyzer(&data);
			if (data.error)
			{
				ft_free_lexer(data.lst_lexer);
				data.general.old_error = data.error;			
				continue;
			}
			ft_expanding(&data);
			ft_change_exit_status(&data);
			ft_parsing(&data);
			ft_delete_quotes(&data);
			execution(&data);
			ft_free_lexer(data.lst_lexer);
			ft_free_cmd(data.lst_cmd);
		}
		data.general.old_error = data.error;
	}
	return (0);
}