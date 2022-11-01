/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:16:08 by yabtaour          #+#    #+#             */
/*   Updated: 2022/09/30 14:40:39 by ssabbaji         ###   ########.fr       */
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

	i = 0;
	index = ft_get_index(cmd, 1);
	r = ft_real_len(cmd);
	len = 0;
	new_cmd = malloc (ft_strlen(cmd) + 1 - r);
	if (!new_cmd)
		exit (1);
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
	char	*temp1;

	cmd_clone = data->lst_cmd;
	while (cmd_clone && cmd_clone->cmd)
	{
		i = 0;
		while (cmd_clone->cmd[i])
		{
			if (ft_exist_quotes(cmd_clone->cmd[i]))
			{
				temp = ft_strdup(cmd_clone->cmd[i]);
				free(cmd_clone->cmd[i]);
				temp1 = ft_delete(temp);
				cmd_clone->cmd[i] = ft_strdup(temp1);
				free(temp1);
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
	char	*temp2;

	temp = NULL;
	if (ft_exist_quotes(eof))
	{
		temp = ft_substr(eof, 0, ft_strlen(eof));
		free(eof);
		temp2 = ft_delete(temp);
		eof = ft_substr(temp2, 0, ft_strlen(temp));
		free(temp2);
		free(temp);
	}
}
