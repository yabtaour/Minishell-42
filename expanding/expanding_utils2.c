/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabtaour <yabtaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:16:24 by yabtaour          #+#    #+#             */
/*   Updated: 2022/07/26 18:16:25 by yabtaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_for_norme(t_data *data, char *value, int i)
{
	if (value[i] == '"' && data->flag_s == 0)
		data->flag_d = ft_change_flag(data->flag_d);
	if (value[i] == '\'' && data->flag_d == 0)
		data->flag_s = ft_change_flag(data->flag_s);
	if (data->flag_s == 0 && value[i] == '$'
		&& value[i + 1]
		&& value[i + 1] != '"'
		&& value[i + 1] != '?')
		return (1);
	return (0);
}

int	ft_check_still_dollar(t_data *data)
{
	t_lexer	*lexer_clone;
	int		i;

	lexer_clone = data->lst_lexer;
	while (lexer_clone)
	{
		if (!ft_strcmp(lexer_clone->value, "<<"))
		{
			lexer_clone = lexer_clone->next;
			if (lexer_clone)
				lexer_clone = lexer_clone->next;
		}
		data->flag_d = 0;
		data->flag_s = 0;
		i = -1;
		while (lexer_clone && lexer_clone->value[++i])
		{
			if (ft_check_for_norme(data, lexer_clone->value, i))
				return (1);
		}
		if (lexer_clone)
			lexer_clone = lexer_clone->next;
	}
	return (0);
}

char	*ft_fix_norme(char *n_v, char *value, int i)
{
	return (ft_strjoin(n_v, ft_substr(value, i, ft_strlen(value))));
}

char	*ft_change_nd_free(char *value, char *var, char *n_v)
{
	free(value);
	value = ft_substr(n_v, 0, ft_strlen(n_v));
	free(var);
	free(n_v);
	return (value);
}
