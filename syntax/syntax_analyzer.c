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
	if ((lexer_clone->type == PIPE)  && !flag)
	{
		printf("Syntax error near unexpected token `%s'\n", lexer_clone->value);
		data->error = 258;
	}
	return (data->error);
}

static int	ft_check_and_or(t_data *data)
{
	t_lexer	*lexer_clone;

	lexer_clone = data->lst_lexer;
	while (lexer_clone)
	{
		if (lexer_clone->type == AND || lexer_clone->type == PARENTHESIS
			|| (lexer_clone->type == PIPE && strlen(lexer_clone->value) > 1)
			|| (lexer_clone->type == SEMI))
		{
			data->error = 258;
			printf("Syntax error near unexpected token `%c'\n", lexer_clone->value[0]);
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
		data->error = ft_check_and_or(data);
		if (data->error)
			return (data->error);
		data->error = ft_check_start_end(data);
		if (data->error)
			return (data->error);
		// data->error = ft_check_quotes(data);
		// if (data->error)
		// 	return (data->error);
		data->error = ft_check_between_pipes(data);
		if (data->error)
			return (data->error);
		data->error = ft_check_redirection(data);
		if (data->error)
			return (data->error);
	}
	return (data->error);
}