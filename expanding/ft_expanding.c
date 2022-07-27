/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expanding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabtaour <yabtaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:16:26 by yabtaour          #+#    #+#             */
/*   Updated: 2022/07/27 17:00:29 by yabtaour         ###   ########.fr       */
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

int	ft_value_var(t_data *data, int i, char *value)
{
	while (value[i] && value[i] != ' ' && value[i] != '$'
		&& value[i] != '\\' && value[i] != '"'
		&& value[i] != '\'' && value[i] != '=')
		i++;
	return (i);
}

void	ft_real_expanding(t_data *data, t_lexer *lexer, char *var, char *n_v)
{
	int		i;
	char	*temp;

	temp = NULL;
	i = 0;
	temp = ft_substr(lexer->value, 0, ft_len_before(lexer->value));
	n_v = ft_strjoin(n_v, temp);
	free(temp);
	i = ft_value_before(data, i, lexer->value);
	if (lexer->value[i] && lexer->value[i + 1])
		var = ft_substr(lexer->value, i + 1, ft_len_var(lexer->value));
	if (var)
	{
		if (ft_check_var_env(data, var))
		{
			n_v = ft_strjoin(n_v, ft_get_value(data, var));
			i++;
			i = ft_value_var(data, i, lexer->value);
			if (lexer->value[i])
				n_v = ft_fix_norme(n_v, lexer->value, i);
		}
		else
			n_v = ft_strjoin(n_v, ft_delete_var(data, lexer->value));
		lexer->value = ft_change_nd_free(lexer->value, var, n_v);
	}
}

void	ft_expanding(t_data *data)
{
	t_lexer	*lexer_clone;
	t_env	*env_clone;
	char	*new_var;
	char	*var;

	lexer_clone = data->lst_lexer;
	while (ft_check_still_dollar(data))
	{
		lexer_clone = data->lst_lexer;
		while (lexer_clone)
		{
			if (!ft_strcmp(lexer_clone->value, "<<"))
			{
				lexer_clone = lexer_clone->next;
				if (lexer_clone)
					lexer_clone = lexer_clone->next;
			}
			var = NULL;
			new_var = NULL;
			if (lexer_clone->type == WORD)
				ft_real_expanding(data, lexer_clone, var, new_var);
			if (lexer_clone)
				lexer_clone = lexer_clone->next;
		}
	}
}
