#include "../minishell.h"

int	ft_check_the_quotes(t_data *data)
{
	int		flag_s = 0;
	int		flag_d = 0;
	int		double_num = 0;
	int		single_num = 0;
	t_lexer	*lexer_clone = data->lst_lexer;
	int		i = 0;

	while (lexer_clone)
	{
		if (lexer_clone->type == WORD)
		{
			i = 0;
			while (lexer_clone->value[i])
			{
				if (lexer_clone->value[i] == '"' && flag_s == 0)
				{
					double_num++;
					flag_d = ft_change_flag(flag_d);
				}
				if (lexer_clone->value[i] == '\'' && flag_d == 0)
				{
					single_num++;
					flag_s = ft_change_flag(flag_s);
				}
				i++;
			}
		}
		lexer_clone = lexer_clone->next;
	}
	if (double_num % 2)
	{
		printf ("Syntax error near unexpected token `\"'\n");
		return (258);
	}
	if (single_num % 2)
	{
		printf ("Syntax error near unexpected token `\''\n");
		return (258);
	}
	return (0);
}

int	ft_check_quotes(t_data *data)
{
	data->error = ft_check_the_quotes(data);
	if (data->error)
		return (data->error);
	return (data->error);
}