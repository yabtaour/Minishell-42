/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabtaour <yabtaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:16:39 by yabtaour          #+#    #+#             */
/*   Updated: 2022/07/26 23:45:37 by yabtaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_add_redirection(t_data *data, int i)
{
	char	*command;
	int		len;
	int		origin;

	origin = i;
	len = 0;
	command = NULL;
	while (data->cmd[i] && ft_is_redirection(data->cmd[i]))
	{
		i++;
		len++;
	}
	command = ft_substr(data->cmd, origin, len);
	data->lst_lexer = ft_add_lexer_back(data->lst_lexer, command, REDIRECTION);
	free(command);
	return (i);
}
