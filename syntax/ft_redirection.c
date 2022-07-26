#include "../minishell.h"

void	ft_for_norme(t_data *data, char *value)
{
	data->error = 258;
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
		data->error = 258;
		printf("Syntax error near unexpected token `newline'\n");
		return (data->error);
	}
	lexer_clone = data->lst_lexer;
	while (lexer_clone)
	{
		if (lexer_clone->type == REDIRECTION && ft_strlen(lexer_clone->value) > 2)
		{
			ft_for_norme(data, lexer_clone->value);
			return (data->error);
		}
		lexer_clone = lexer_clone->next;
	}
	return (data->error);
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
					ft_for_norme(data, lexer_clone->value);
					return (data->error);
				}
				else
					break ;
				lexer_clone = lexer_clone->next;
			}
		}
		lexer_clone = lexer_clone->next;
	}
	return (data->error);
}

int	ft_check_redirection(t_data *data)
{	
	data->error = ft_check_red(data);
	if (data->error)
		return (data->error);
	data->error = ft_check_after_red(data);
	if (data->error)
		return (data->error);
	return (data->error);
}
