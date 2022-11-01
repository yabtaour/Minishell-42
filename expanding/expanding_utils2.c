/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:16:24 by yabtaour          #+#    #+#             */
/*   Updated: 2022/09/15 18:08:28 by ssabbaji         ###   ########.fr       */
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
		&& value[i + 1] != '\''
		&& value[i + 1] != '?'
		&& value[i + 1] != '+'
		&& value[i + 1] != '-'
		&& value[i + 1] != '/'
		&& value[i + 1] != '%')
		return (1);
	return (0);
}

char	*ft_get_expand_value(char *n_v, int i, char *lexer)
{
	i++;
	i = ft_value_var(i, lexer);
	if (lexer[i])
		n_v = ft_fix_norme(n_v, lexer, i);
	return (n_v);
}

int	ft_check_still_dollar(t_data *data)
{
	t_lexer	*lexer_clone;
	int		i;

	lexer_clone = data->lst_lexer;
	while (lexer_clone)
	{
		if (!ft_strcmp(lexer_clone->val, "<<"))
		{
			lexer_clone = lexer_clone->next;
			if (lexer_clone)
				lexer_clone = lexer_clone->next;
		}
		data->flag_d = 0;
		data->flag_s = 0;
		i = -1;
		while (lexer_clone && lexer_clone->val[++i])
		{
			if (ft_check_for_norme(data, lexer_clone->val, i))
				return (1);
		}
		if (lexer_clone)
			lexer_clone = lexer_clone->next;
	}
	return (0);
}

char	*ft_fix_norme(char *n_v, char *value, int i)
{
	char	*after;
	char	*new;

	after = ft_substr(value, i, ft_strlen(value));
	new = ft_strjoin(n_v, after);
	free(after);
	return (new);
}

char	*ft_change_nd_free(char *var, char *n_v)
{
	char	*new;

	new = ft_substr(n_v, 0, ft_strlen(n_v));
	free(var);
	free(n_v);
	return (new);
}
