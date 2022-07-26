/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabtaour <yabtaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:16:08 by yabtaour          #+#    #+#             */
/*   Updated: 2022/07/26 18:20:44 by yabtaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exist(int i, int *index, int len)
{
	int	idx;

	idx = 0;
	while (idx < len)
	{
		if (index[idx] == i)
			return (1);
		idx++;
	}
	return (0);
}

int	ft_exist_quotes(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '"' || cmd[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_delete(char *cmd)
{
	int		*index;
	int		i;
	int		len;
	int		r;
	char	*new_cmd;

	index = ft_get_index(cmd, 1);
	r = ft_real_len(cmd);
	len = 0;
	new_cmd = malloc (ft_strlen(cmd) + 1 - r);
	while (cmd[i])
	{
		if (!ft_exist(i, index, r))
		{
			new_cmd[len] = cmd[i];
			len++;
		}
		i++;
	}
	new_cmd[len] = '\0';
	free(index);
	return (new_cmd);
}

void	ft_delete_quotes(t_data *data)
{
	t_cmd	*cmd_clone;
	char	*temp;
	int		i;
	int		len;

	cmd_clone = data->lst_cmd;
	temp = NULL;
	while (cmd_clone && cmd_clone->cmd)
	{
		i = 0;
		while (cmd_clone->cmd[i])
		{
			if (ft_exist_quotes(cmd_clone->cmd[i]))
			{
				len = ft_strlen(cmd_clone->cmd[i]);
				temp = ft_substr(cmd_clone->cmd[i], 0, len);
				free(cmd_clone->cmd[i]);
				len = ft_strlen(temp);
				cmd_clone->cmd[i] = ft_substr(ft_delete(temp), 0, len);
				free(temp);
			}
			i++;
		}
		cmd_clone = cmd_clone->next;
	}
}

void	ft_delete_eof_quotes(char *eof)
{
	char	*temp;

	temp = NULL;
	if (ft_exist_quotes(eof))
	{
		temp = ft_substr(eof, 0, ft_strlen(eof));
		free(eof);
		eof = ft_substr(ft_delete(temp), 0, ft_strlen(temp));
		free(temp);
	}
}
