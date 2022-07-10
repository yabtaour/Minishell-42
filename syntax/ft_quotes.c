#include "../minishell.h"

static int	ft_check_double(t_data *data)
{
	int		double_num;
	t_lexer	*lexer_clone;
	int		i;

	double_num = 0;
	lexer_clone = data->lst_lexer;
	while (lexer_clone)
	{
		i = 1;
		if (lexer_clone->type == DOUBLE_QUOTES)
		{
			while (lexer_clone->value[i])
			{
				if (lexer_clone->value[i] == '"')
					double_num++;
				i++;
			}
			double_num++;
		}
		lexer_clone = lexer_clone->next;
	}
	if ((double_num % 2) != 0)
	{
		data->error = 258;
		printf("Syntax error near unexpected token `\"'\n");
	}
	return (data->error);
}

static int	ft_check_single(t_data *data)
{
	int		single_num;
	t_lexer	*lexer_clone;
	int		i;

	single_num = 0;
	lexer_clone = data->lst_lexer;
	while (lexer_clone)
	{
		i = 1;
		if (lexer_clone->type == SINGLE_QUOTES)
		{
			while (lexer_clone->value[i])
			{
				if (lexer_clone->value[i] == '\'')
					single_num++;
				i++;
			}
			single_num++;
		}
		lexer_clone = lexer_clone->next;
	}
	if ((single_num % 2) != 0)
	{
		data->error = 258;
		printf("Syntax error near unexpected token `\''\n");
	}
	return (data->error);
}

int	ft_check_quotes(t_data *data)
{
	ft_print_lexer(data->lst_lexer);
	data->error = ft_check_double(data);
	if (data->error)
		return (data->error);
	data->error = ft_check_single(data);
	if (data->error)
		return (data->error);
	return (data->error);
}