/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 17:56:21 by yabtaour          #+#    #+#             */
/*   Updated: 2022/09/19 16:30:06 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_change_env_value(t_data *data, char *name, char *value)
{
	t_env	*env_clone;

	env_clone = data->lst_env;
	while (env_clone)
	{
		if (ft_strcmp(name, env_clone->name) == 0)
		{
			if (value)
			{
				free(env_clone->value);
				if (value[0] == '\0')
				{
					env_clone->value = malloc (1);
					env_clone->value[0] = '\0';
				}
				else
					env_clone->value = ft_substr(value, 0, ft_strlen(value));
			}
		}
		env_clone = env_clone->next;
	}
	free(name);
	if (value)
		free(value);
	return (0);
}

int	ft_name_exists(t_data *data, char *name)
{
	t_env	*env_clone;

	if (!name)
		return (0);
	env_clone = data->lst_env;
	while (env_clone)
	{
		if (ft_strcmp(name, env_clone->name) == 0)
			return (1);
		env_clone = env_clone->next;
	}
	return (0);
}

char	*ft_get_name_exp(char *name)
{
	int		i;
	char	*new_name;

	new_name = NULL;
	i = 0;
	if (!name)
		return (NULL);
	while (name[i] && name[i] != '=')
		i++;
	new_name = ft_substr(name, 0, i);
	return (new_name);
}

char	*export_no_value(char *value, int idx)
{
	char	*new;

	if (value[idx] == '\0')
	{
		new = malloc(sizeof(char) * 1);
		new[0] = '\0';
		return (new);
	}
	return (NULL);
}

char	*ft_get_value_exp(char *value)
{
	int		i;
	int		j;
	int		origin;
	char	*new_value;

	i = 0;
	j = 0;
	new_value = NULL;
	if (!value)
		return (NULL);
	while (value[i] && value[i] != '=')
		i++;
	if (value[i])
	{
		origin = i + 1;
		new_value = export_no_value(value, origin);
		if (new_value)
			return (new_value);
		while (value[++i])
			j++;
		new_value = ft_substr(value, origin, j);
	}
	return (new_value);
}
