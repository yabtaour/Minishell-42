/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:17:27 by yabtaour          #+#    #+#             */
/*   Updated: 2022/09/25 17:05:16 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_output_err(t_data *data, char *value)
{
	(void)data;
	g_vars.g_exit_stat = 258;
	printf("Syntax error near unexpected token `%s'\n", value);
}

static int	ft_check_red(t_data *data)
{
	t_lexer	*lexer_clone;

	lexer_clone = data->lst_lexer;
	while (lexer_clone->next)
		lexer_clone = lexer_clone->next;
	if (lexer_clone->type == REDIRECTION)
	{
		g_vars.g_exit_stat = 258;
		printf("Syntax error near unexpected token `newline'\n");
		return (258);
	}
	lexer_clone = data->lst_lexer;
	while (lexer_clone)
	{
		if (lexer_clone->type == REDIRECTION
			&& ft_strlen(lexer_clone->val) > 2)
		{
			ft_output_err(data, lexer_clone->val);
			return (g_vars.g_exit_stat);
		}
		lexer_clone = lexer_clone->next;
	}
	return (g_vars.g_exit_stat);
}

static int	ft_check_type(int lexer_clone_type)
{
	if (lexer_clone_type == PIPE || lexer_clone_type == REDIRECTION)
		return (1);
	return (0);
}

static int	ft_check_after_red(t_data *data)
{
	t_lexer	*lexer_clone;

	lexer_clone = data->lst_lexer;
	while (lexer_clone)
	{
		if (lexer_clone->type == REDIRECTION)
		{
			lexer_clone = lexer_clone->next;
			while (lexer_clone->next)
			{
				if (ft_check_type(lexer_clone->type))
				{
					ft_output_err(data, lexer_clone->val);
					return (g_vars.g_exit_stat);
				}
				else
					break ;
				lexer_clone = lexer_clone->next;
			}
		}
		lexer_clone = lexer_clone->next;
	}
	return (g_vars.g_exit_stat);
}

int	ft_check_redirection(t_data *data)
{	
	g_vars.g_exit_stat = ft_check_red(data);
	if (g_vars.g_exit_stat)
		return (g_vars.g_exit_stat);
	g_vars.g_exit_stat = ft_check_after_red(data);
	if (g_vars.g_exit_stat)
		return (g_vars.g_exit_stat);
	return (g_vars.g_exit_stat);
}
