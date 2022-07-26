/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabtaour <yabtaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:17:34 by yabtaour          #+#    #+#             */
/*   Updated: 2022/07/26 18:17:36 by yabtaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_env(t_data *data, char *name)
{
	t_env	*env_clone;

	env_clone = data->lst_env;
	if (!name)
		return (NULL);
	while (env_clone)
	{
		if (ft_strncmp(name, env_clone->name, ft_strlen(name)) == 0)
			return (env_clone->value);
		env_clone = env_clone->next;
	}
	return (NULL);
}
