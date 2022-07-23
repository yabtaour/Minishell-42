#include "../minishell.h"

int	ft_check_which(int double_num, int single_num)
{
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

int	ft_change_double(t_data *data, char c, int quote)
{
	if (c == '"' && data->flag_s == 0)
	{
		quote++;
		data->flag_d = ft_change_flag(data->flag_d);
	}
	return (quote);
}

int	ft_change_single(t_data *data, char c, int quote)
{
	if (c == '\'' && data->flag_d == 0)
	{
		quote++;
		data->flag_s = ft_change_flag(data->flag_s);
	}
	return (quote);
}

int	ft_check_the_quotes(t_data *data)
{
	int		do_num;
	int		si_num;
	t_lexer	*lexer_clone;
	int		i;

	data->flag_d = 0;
	data->flag_s = 0;
	do_num = 0;
	si_num = 0;
	lexer_clone = data->lst_lexer;
	while (lexer_clone)
	{
		if (lexer_clone->type == WORD)
		{
			i = 0;
			while (lexer_clone->value[i])
			{
				do_num = ft_change_double(data, lexer_clone->value[i], do_num);
				si_num = ft_change_single(data, lexer_clone->value[i], si_num);
				i++;
			}
		}
		lexer_clone = lexer_clone->next;
	}
	return (ft_check_which(do_num, si_num));
}

int	ft_check_quotes(t_data *data)
{
	data->error = ft_check_the_quotes(data);
	return (data->error);
}
