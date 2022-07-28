/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsaf <rsaf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:16:51 by yabtaour          #+#    #+#             */
/*   Updated: 2022/07/28 12:52:34 by rsaf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lexer(t_data *data)
{
	int		i;

	i = 0;
	data->cmd = ft_strtrim(data->cmd, " ");
	add_history(data->cmd);
	while (data->cmd[i])
	{
		while (data->cmd[i] == ' ')
			i++;
		if (data->cmd[i] != '&' && data->cmd[i] != '|'
			&& !ft_is_redirection(data->cmd[i]))
			i = ft_add_word(data, i);
		if (ft_is_redirection(data->cmd[i]))
			i = ft_add_redirection(data, i);
		if (data->cmd[i] == '&')
			i = ft_add_and(data, i);
		if (data->cmd[i] == '|')
			i = ft_add_pipe(data, i);
		if (ft_is_parenth(data->cmd[i]))
			i = ft_add_parenth(data, i);
		if (data->cmd[i] == ';')
			i = ft_add_semi(data, i);
	}
	free(data->cmd);
}
