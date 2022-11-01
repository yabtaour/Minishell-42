/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:17:29 by yabtaour          #+#    #+#             */
/*   Updated: 2022/09/27 17:42:40 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check_start_end(t_data *data)
{
	t_lexer	*lexer_clone;
	int		flag;

	flag = 0;
	lexer_clone = data->lst_lexer;
	if (lexer_clone->type == PIPE)
	{
		flag = 1;
		printf("Syntax error near unexpected token `%s'\n", lexer_clone->val);
		g_vars.g_exit_stat = 258;
	}
	while (lexer_clone->next)
		lexer_clone = lexer_clone->next;
	if ((lexer_clone->type == PIPE) && !flag)
	{
		printf("Syntax error near unexpected token `%s'\n", lexer_clone->val);
		g_vars.g_exit_stat = 258;
	}
	return (g_vars.g_exit_stat);
}

static int	ft_check_forbidden(t_data *data)
{
	t_lexer	*lexer_clone;
	char	c;

	lexer_clone = data->lst_lexer;
	while (lexer_clone)
	{
		if (lexer_clone->type == AND || lexer_clone->type == PARENTHESIS
			|| (lexer_clone->type == PIPE && ft_strlen(lexer_clone->val) > 1)
			|| (lexer_clone->type == SEMI))
		{
			g_vars.g_exit_stat = 258;
			c = lexer_clone->val[0];
			printf("Syntax error near unexpected token `%c'\n", c);
			return (g_vars.g_exit_stat);
		}
		lexer_clone = lexer_clone->next;
	}
	return (g_vars.g_exit_stat);
}

int	ft_syntax_analyzer(t_data *data)
{
	if (data->lst_lexer)
	{
		g_vars.g_exit_stat = ft_check_forbidden(data);
		if (g_vars.g_exit_stat)
			return (g_vars.g_exit_stat);
		g_vars.g_exit_stat = ft_check_start_end(data);
		if (g_vars.g_exit_stat)
			return (g_vars.g_exit_stat);
		g_vars.g_exit_stat = ft_check_quotes(data);
		if (g_vars.g_exit_stat)
			return (g_vars.g_exit_stat);
		g_vars.g_exit_stat = ft_check_between_pipes(data);
		if (g_vars.g_exit_stat)
			return (g_vars.g_exit_stat);
		g_vars.g_exit_stat = ft_check_redirection(data);
		if (g_vars.g_exit_stat)
			return (g_vars.g_exit_stat);
	}
	return (g_vars.g_exit_stat);
}
