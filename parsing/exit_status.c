/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabtaour <yabtaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:16:59 by yabtaour          #+#    #+#             */
/*   Updated: 2022/07/26 19:48:20 by yabtaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_allocate(char *exit, char *value)
{
	int		len;
	char	*new;

	len = ft_strlen(exit) + ft_strlen(value) - 2;
	new = malloc(sizeof(char) * len - 1);
	if (!new)
		return (NULL);
	return (new);
}

char	*ft_new_value(t_data *data, char *value)
{
	char	*exit_s;
	char	*new_value;
	int		i;
	int		j;

	j = 0;
	i = 0;
	new_value = ft_allocate(ft_itoa(data->general.old_error), value);
	while (value[i])
	{
		if (value[i] == '$' && value[i + 1] == '?')
		{
			new_value = ft_strjoin(new_value, ft_itoa(data->general.old_error));
			j += ft_strlen(ft_itoa(data->general.old_error));
			i += 2;
		}
		else
		{
			new_value[j] = value[i];
			j++;
			i++;
		}
	}
	new_value[j] = '\0';
	return (new_value);
}

char	*ft_change_value(t_data *data, char *value)
{
	char	*temp;

	temp = ft_substr(value, 0, ft_strlen(value));
	free(value);
	value = ft_new_value(data, temp);
	free(temp);
	return (value);
}

void	ft_change_exit_status(t_data *data)
{
	t_lexer	*lexer_clone;
	int		i;

	lexer_clone = data->lst_lexer;
	while (lexer_clone)
	{
		data->flag_d = 0;
		data->flag_s = 0;
		i = 0;
		while (lexer_clone->value[i])
		{
			if (lexer_clone->value[i] == '"' && data->flag_s == 0)
				ft_change_flag(data->flag_d);
			if (lexer_clone->value[i] == '\'' && data->flag_d == 0)
				ft_change_flag(data->flag_s);
			if (data->flag_s == 0 && lexer_clone->value[i] == '$'
				&& lexer_clone->value[i + 1] == '?')
				lexer_clone->value = ft_change_value(data, lexer_clone->value);
			i++;
		}
		lexer_clone = lexer_clone->next;
	}
}
