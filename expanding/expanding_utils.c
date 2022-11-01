/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabtaour <yabtaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:16:21 by yabtaour          #+#    #+#             */
/*   Updated: 2022/07/26 18:16:22 by yabtaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_change_flag(int flag)
{
	if (flag == 0)
		return (1);
	if (flag == 0)
		return (0);
	return (0);
}

char	*ft_get_value(t_data *data, char *var)
{
	t_env	*env_clone;

	env_clone = data->lst_env;
	while (env_clone)
	{
		if (!ft_strcmp(env_clone->name, var))
			return (env_clone->value);
		env_clone = env_clone->next;
	}
	return (NULL);
}

int	ft_check_var_env(t_data *data, char *var)
{
	t_env	*env_clone;

	env_clone = data->lst_env;
	while (env_clone)
	{
		if (!ft_strcmp(env_clone->name, var))
			return (1);
		env_clone = env_clone->next;
	}
	return (0);
}

char	*ft_delete_variable(char *var, int i)
{
	char	*new;

	i++;
	new = NULL;
	while (var[i] && !ft_isspace(var[i]) && var[i] != '$'
		&& var[i] != '\\' && var[i] != '"' && var[i] != '='
		&& var[i] != '\'')
	{
		i++;
		if (var[i] >= '0' && var[i] <= '9')
			break ;
	}
	if (var[i])
		new = ft_substr(var, i, ft_len_after(var));
	return (new);
}

char	*ft_delete_var(t_data *data, char *var)
{
	char	*new_var;
	int		i;

	i = 0;
	data->flag_s = 0;
	data->flag_d = 0;
	new_var = NULL;
	while (data->flag_s == 1 || (var[i] && var[i] != '$'))
	{
		if (var[i] == '"' && data->flag_s == 0)
			data->flag_d = ft_change_flag(data->flag_d);
		if (var[i] == '\'' && data->flag_d == 0)
			data->flag_s = ft_change_flag(data->flag_s);
		i++;
	}
	if (data->flag_s == 0 && var[i] && var[i] == '$')
		new_var = ft_delete_variable(var, i);
	return (new_var);
}
