/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabtaour <yabtaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:17:29 by yabtaour          #+#    #+#             */
/*   Updated: 2022/07/26 18:17:30 by yabtaour         ###   ########.fr       */
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
		printf("Syntax error near unexpected token `%s'\n", lexer_clone->value);
		data->error = 258;
	}
	while (lexer_clone->next)
		lexer_clone = lexer_clone->next;
	if ((lexer_clone->type == PIPE) && !flag)
	{
		printf("Syntax error near unexpected token `%s'\n", lexer_clone->value);
		data->error = 258;
	}
	return (data->error);
}

static int	ft_check_forbidden(t_data *data)
{
	t_lexer	*lexer_clone;
	char	c;

	lexer_clone = data->lst_lexer;
	while (lexer_clone)
	{
		if (lexer_clone->type == AND || lexer_clone->type == PARENTHESIS
			|| (lexer_clone->type == PIPE && ft_strlen(lexer_clone->value) > 1)
			|| (lexer_clone->type == SEMI))
		{
			data->error = 258;
			c = lexer_clone->value[0];
			printf("Syntax error near unexpected token `%c'\n", c);
			return (data->error);
		}
		lexer_clone = lexer_clone->next;
	}
	return (data->error);
}

int	ft_syntax_analyzer(t_data *data)
{
	int	id_pipe;
	int	id_redirection;

	if (data->lst_lexer)
	{
		data->error = ft_check_forbidden(data);
		if (data->error)
			return (data->error);
		data->error = ft_check_start_end(data);
		if (data->error)
			return (data->error);
		data->error = ft_check_quotes(data);
		if (data->error)
			return (data->error);
		data->error = ft_check_between_pipes(data);
		if (data->error)
			return (data->error);
		data->error = ft_check_redirection(data);
		if (data->error)
			return (data->error);
	}
	return (data->error);
}
