/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 17:56:24 by yabtaour          #+#    #+#             */
/*   Updated: 2022/09/25 17:34:54 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_swap_name(t_env *clone1, t_env *clone2)
{
	char	*name_tmp;

	name_tmp = ft_substr(clone1->name, 0, ft_strlen(clone1->name));
	if (clone1->name)
		free(clone1->name);
	clone1->name = ft_substr(clone2->name, 0, ft_strlen(clone2->name));
	if (clone2->name)
		free(clone2->name);
	clone2->name = ft_substr(name_tmp, 0, ft_strlen(name_tmp));
	if (name_tmp)
		free(name_tmp);
}

void	ft_swap_value(t_env *clone1, t_env *clone2)
{
	char	*value_tmp;
	int		len;

	len = ft_strlen(clone1->value);
	value_tmp = ft_substr(clone1->value, 0, len);
	if (clone1->value)
		free(clone1->value);
	len = ft_strlen(clone2->value);
	clone1->value = ft_substr(clone2->value, 0, len);
	if (clone2->value)
		free(clone2->value);
	len = ft_strlen(value_tmp);
	clone2->value = ft_substr(value_tmp, 0, len);
	if (value_tmp)
		free(value_tmp);
}

void	ft_sort_original(t_data *data)
{
	t_env	*env_clone;
	t_env	*env_clone2;

	env_clone = data->lst_env;
	while (env_clone)
	{
		env_clone2 = env_clone->next;
		while (env_clone2)
		{
			if (ft_strcmp(env_clone->name, env_clone2->name) > 0)
			{
				ft_swap_name(env_clone, env_clone2);
				ft_swap_value(env_clone, env_clone2);
			}
			env_clone2 = env_clone2->next;
		}
		env_clone = env_clone->next;
	}
}

void	ft_sort_env(t_data *data)
{
	t_env	*env_clone;

	env_clone = data->lst_env;
	ft_sort_original(data);
}
