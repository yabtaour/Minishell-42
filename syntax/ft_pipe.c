#include "../minishell.h"

int	ft_skip_norme(t_lexer *lexer_clone, int num)
{
	lexer_clone = lexer_clone->next;
	while (lexer_clone && lexer_clone->type != PIPE)
	{
		num++;
		lexer_clone = lexer_clone->next;
	}
	return (num);
}

int	ft_idk(t_data *data, t_lexer *lexer_clone, int num)
{
	if (lexer_clone && lexer_clone->type == PIPE && num == 0)
	{
		printf("Syntax error near unexpected token `|'\n");
		data->error = 258;
	}
	return (0);
}

int	ft_check_between_pipes(t_data *data)
{
	t_lexer	*lexer_clone;
	int		num;

	lexer_clone = data->lst_lexer;
	while (lexer_clone)
	{
		num = 0;
		if (lexer_clone->type == PIPE)
		{
			lexer_clone = lexer_clone->next;
			while (lexer_clone && lexer_clone->type != PIPE)
			{
				num++;
				lexer_clone = lexer_clone->next;
			}
			if (!lexer_clone)
				break ;
			if (ft_idk(data, lexer_clone, num))
				break ;
		}
		if (lexer_clone->type != PIPE)
			lexer_clone = lexer_clone->next;
	}
	return (data->error);
}
