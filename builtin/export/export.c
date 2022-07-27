/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabtaour <yabtaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 17:56:29 by yabtaour          #+#    #+#             */
/*   Updated: 2022/07/27 19:59:55 by yabtaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_print_export(t_data *data)
{
	t_env	*env_clone;

	env_clone = data->lst_env;
	while (env_clone)
	{
		printf("declare -x ");
		printf("%s", env_clone->name);
		if (env_clone->value && ft_strlen(env_clone->value))
			printf("=\"%s\"", env_clone->value);
		printf("\n");
		env_clone = env_clone->next;
	}
}

void	ft_export_arg(t_data *data, t_cmd *lst_cmd, int fd)
{
	char	*name;
	char	*value;
	int		i;

	i = 1;
	while (lst_cmd->cmd[i])
	{
		name = ft_get_name_exp(lst_cmd->cmd[i]);
		value = ft_get_value_exp(lst_cmd->cmd[i]);
		if (ft_name_exists(data, name))
			ft_change_env_value(data, name, value, ft_strlen(value));
		else
		{
			ft_add_new_env(data, name, value);
			if (!data->first_export)
				data->first_export = ft_substr(name, 0, ft_strlen(name));
		}
		free(name);
		free(value);
		i++;
	}
}

int	export(t_data *data, t_cmd *lst_cmd, int fd)
{
	if (lst_cmd && !lst_cmd->cmd[1])
	{
		ft_sort_env(data);
		ft_print_export(data);
	}
	else
		ft_export_arg(data, lst_cmd, fd);
	return (0);
}
