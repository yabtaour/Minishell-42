/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 10:38:50 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/10/02 10:38:53 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_check_concate(char *name)
{
	if (name[ft_strlen(name) - 1] == '+')
		return (1);
	return (0);
}

void	ft_new_concate(t_data *data, char *name, char *value)
{
	ft_add_new_env(data, name, value);
	if (name)
		free(name);
	if (value)
		free(value);
}

char	*ft_get_concate_name(char *name)
{
	char	*temp;

	temp = ft_substr(name, 0, ft_strlen(name) - 1);
	free(name);
	name = ft_strdup(temp);
	free(temp);
	return (name);
}

void	ft_concatenate(t_data *data, char *name, char *value)
{
	char	*temp;
	t_env	*env_clone;

	env_clone = data->lst_env;
	name = ft_get_concate_name(name);
	if (ft_name_exists(data, name))
	{
		while (env_clone)
		{
			if (!ft_strcmp(env_clone->name, name))
			{
				temp = env_clone->value;
				env_clone->value = ft_strjoin(temp, value);
				break ;
			}
			env_clone = env_clone->next;
		}
		free(name);
		free(value);
	}
	else
		ft_new_concate(data, name, value);
}
