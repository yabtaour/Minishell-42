/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expanding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:16:26 by yabtaour          #+#    #+#             */
/*   Updated: 2022/09/30 14:34:02 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_value_before(t_data *data, int i, char *value)
{
	i = 0;
	data->flag_s = 0;
	data->flag_d = 0;
	while (data->flag_s == 1 || (value[i] && value[i] != '$'))
	{
		if (value[i] == '"' && data->flag_s == 0)
			data->flag_d = ft_change_flag(data->flag_d);
		if (value[i] == '\'' && data->flag_d == 0)
			data->flag_s = ft_change_flag(data->flag_s);
		i++;
	}
	return (i);
}

int	ft_value_var(int i, char *value)
{
	while (value[i] && !ft_isspace(value[i]) && value[i] != '$'
		&& value[i] != '\\' && value[i] != '"'
		&& value[i] != '\'' && value[i] != '='
		&& value[i] != '+'
		&& value[i] != '-'
		&& value[i] != '/'
		&& value[i] != '%')
		i++;
	return (i);
}

void	ft_real_expanding(t_data *data, t_lexer *lexer)
{
	int		i;
	char	*n_v;
	char	*var;

	i = 0;
	var = NULL;
	n_v = ft_substr(lexer->val, 0, ft_len_before(lexer->val));
	i = ft_value_before(data, i, lexer->val);
	if (lexer->val[i] && lexer->val[i + 1])
		var = ft_substr(lexer->val, i + 1, ft_len_var(lexer->val));
	if (var)
	{
		if (ft_check_var_env(data, var))
		{
			n_v = ft_strjoin(n_v, ft_get_value(data, var));
			n_v = ft_get_expand_value(n_v, i, lexer->val);
		}
		else
			n_v = ft_var_isnt(data, lexer->val, n_v);
		free(lexer->val);
		lexer->val = ft_change_nd_free(var, n_v);
	}
}

int	ft_has_var(t_data *data, char *value)
{
	int	i;

	i = 0;
	while (value && value[i])
	{
		if (value[i] == '"' && data->flag_s == 0)
			data->flag_d = ft_change_flag(data->flag_d);
		if (value[i] == '\'' && data->flag_d == 0)
			data->flag_s = ft_change_flag(data->flag_s);
		if (data->flag_s == 0 && value[i] == '$'
			&& value[i + 1]
			&& value[i + 1] != '"'
			&& value[i + 1] != '\''
			&& value[i + 1] != '?'
			&& value[i + 1] != '+'
			&& value[i + 1] != '-'
			&& value[i + 1] != '/'
			&& value[i + 1] != '%')
			return (1);
		i++;
	}
	return (0);
}

void	ft_expanding(t_data *data)
{
	t_lexer	*lexer_clone;

	lexer_clone = data->lst_lexer;
	while (ft_check_still_dollar(data))
	{
		lexer_clone = data->lst_lexer;
		while (lexer_clone)
		{
			if (!ft_strcmp(lexer_clone->val, "<<"))
			{
				lexer_clone = lexer_clone->next;
				if (lexer_clone)
					lexer_clone = lexer_clone->next;
			}
			if (lexer_clone->type == WORD && ft_has_var(data, lexer_clone->val))
				ft_real_expanding(data, lexer_clone);
			if (lexer_clone)
				lexer_clone = lexer_clone->next;
		}
	}
}
