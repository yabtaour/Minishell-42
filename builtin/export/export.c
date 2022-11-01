/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 17:56:29 by yabtaour          #+#    #+#             */
/*   Updated: 2022/09/25 17:35:01 by ssabbaji         ###   ########.fr       */
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
		if (env_clone->value)
			printf("=\"%s\"", env_clone->value);
		printf("\n");
		env_clone = env_clone->next;
	}
}

int	valid_name(char *name, t_data **data)
{
	if ((name[0] >= 33 && name[0] < 65) || name[0] == '\0')
	{
		printf("bash: export: `%s': not a valid identifier\n", name);
		(*data)->exit_stat = 1;
		return (0);
	}
	return (1);
}

void	ft_normal_export(t_data *data, char *name, char *value)
{
	if (ft_name_exists(data, name))
		ft_change_env_value(data, name, value);
	else
	{
		ft_add_new_env(data, name, value);
		free(name);
		if (value)
			free(value);
	}
}

int	ft_export_arg(t_data *data, t_cmd *lst_cmd, char *name, char *value)
{
	int		i;

	i = 1;
	while (lst_cmd->cmd[i])
	{
		name = ft_get_name_exp(lst_cmd->cmd[i]);
		value = ft_get_value_exp(lst_cmd->cmd[i]);
		if (valid_name(name, &data))
		{
			if (ft_check_concate(name))
				ft_concatenate(data, name, value);
			else
				ft_normal_export(data, name, value);
		}
		else
		{
			if (name)
				free(name);
			if (value)
				free(value);
		}
		i++;
	}
	return (0);
}

int	export(t_data *data, t_cmd *lst_cmd)
{
	char	*name;
	char	*value;

	name = NULL;
	value = NULL;
	if (lst_cmd && !lst_cmd->cmd[1])
	{
		ft_sort_env(data);
		ft_print_export(data);
	}
	else
		return (ft_export_arg(data, lst_cmd, name, value));
	return (0);
}
