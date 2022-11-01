/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabtaour <yabtaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 17:56:26 by yabtaour          #+#    #+#             */
/*   Updated: 2022/07/27 17:56:27 by yabtaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*ft_new_node(char *name, char *value)
{
	t_env	*node;

	node = malloc (sizeof(t_env));
	if (!node)
		exit (1);
	if (name)
		node->name = ft_substr(name, 0, ft_strlen(name));
	if (!node->name)
		exit (1);
	if (value)
	{
		if (ft_strlen(value))
			node->value = ft_substr(value, 0, ft_strlen(value));
		else
		{
			node->value = malloc (sizeof(char) * 1);
			node->value[0] = '\0';
		}
	}
	else
		node->value = NULL;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	ft_add_new_env(t_data *data, char *name, char *value)
{
	t_env	*env_clone;
	t_env	*new_node;

	env_clone = data->lst_env;
	new_node = ft_new_node(name, value);
	if (!env_clone)
	{
		if (new_node)
			data->lst_env = new_node;
		return ;
	}
	while (env_clone->next)
		env_clone = env_clone->next;
	if (new_node)
	{
		env_clone->next = new_node;
		new_node->prev = env_clone;
	}
}
