/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsaf <rsaf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:23:01 by rsaf              #+#    #+#             */
/*   Updated: 2022/07/26 12:23:02 by rsaf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// this function get the path and splited to parts through ':'
void	ft_get_paths(t_data *data)
{
	int		idx;
	char	*path;

	idx = 0;
	path = ft_get_env(data, "PATH");
	if (path)
		data->paths = ft_split(path, ':');
}
