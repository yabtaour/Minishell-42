/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:16:44 by yabtaour          #+#    #+#             */
/*   Updated: 2022/09/19 16:29:41 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_word_len(char *cmd, int i)
{
	int		len;
	char	c;

	len = 0;
	while (cmd[i] && ft_is_word(cmd[i]))
	{
		if (cmd[i] == '"' || cmd[i] == '\'')
		{
			c = cmd[i];
			i++;
			len++;
			while (cmd[i] && cmd[i] != c)
			{
				i++;
				len++;
			}
		}
		len++;
		i++;
	}
	return (len);
}

int	ft_add_word(t_data *data, int i)
{
	char	*command;

	command = ft_substr(data->cmd, i, ft_word_len(data->cmd, i));
	i += ft_word_len(data->cmd, i);
	data->lst_lexer = ft_add_lexer_back(data->lst_lexer, command, WORD);
	free(command);
	return (i);
}
