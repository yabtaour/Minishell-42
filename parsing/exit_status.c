/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:16:59 by yabtaour          #+#    #+#             */
/*   Updated: 2022/09/30 14:46:24 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_allocate(char *exit, char *value)
{
	int		len;
	char	*new;

	len = ft_strlen(exit) + ft_strlen(value) - 2;
	new = malloc(sizeof(char) * len + 1);
	if (!new)
		return (NULL);
	return (new);
}

void	ft_mamak(t_data *data, t_uwu *uwu)
{
	while (uwu->lexer[uwu->i])
	{
		if (uwu->lexer[uwu->i] == '"' && data->flag_s == 0)
			data->flag_d = ft_change_flag(data->flag_d);
		if (uwu->lexer[uwu->i] == '\'' && data->flag_d == 0)
			data->flag_s = ft_change_flag(data->flag_s);
		if (data->flag_s == 0 && uwu->lexer[uwu->i] == '$'
			&& uwu->lexer[uwu->i + 1] == '?')
		{
			uwu->new[uwu->j] = '\0';
			uwu->new = ft_strjoin(uwu->new, uwu->temp);
			uwu->j += ft_strlen(uwu->temp);
			uwu->i += 2;
		}
		else
		{
			uwu->new[uwu->j] = uwu->lexer[uwu->i];
			uwu->j++;
			uwu->i++;
		}
	}
}

char	*ft_new_value(t_data *data, char *lexer)
{
	t_uwu	uwu;

	uwu.i = 0;
	uwu.j = 0;
	uwu.temp = NULL;
	uwu.new = NULL;
	uwu.lexer = lexer;
	data->flag_d = 0;
	data->flag_s = 0;
	uwu.temp = ft_itoa(data->general.old_error);
	uwu.new = ft_allocate(uwu.temp, lexer);
	ft_mamak(data, &uwu);
	free(uwu.temp);
	uwu.new[uwu.j] = '\0';
	return (uwu.new);
}

char	*ft_change_value(t_data *data, char *value)
{
	char	*temp;

	temp = ft_strdup(value);
	free(value);
	value = ft_new_value(data, temp);
	free(temp);
	return (value);
}

void	ft_change_exit_status(t_data *data)
{
	t_lexer	*lexer_clone;
	int		i;
	int		flag_d;
	int		flag_s;

	flag_d = 0;
	flag_s = 0;
	lexer_clone = data->lst_lexer;
	while (lexer_clone)
	{
		i = 0;
		while (lexer_clone->val[i])
		{
			if (lexer_clone->val[i] == '"' && flag_s == 0)
				flag_d = ft_change_flag(flag_d);
			if (lexer_clone->val[i] == '\'' && flag_d == 0)
				flag_s = ft_change_flag(flag_s);
			if (flag_s == 0 && lexer_clone->val[i] == '$'
				&& lexer_clone->val[i + 1] == '?')
				lexer_clone->val = ft_change_value(data, lexer_clone->val);
			i++;
		}
		lexer_clone = lexer_clone->next;
	}
}
