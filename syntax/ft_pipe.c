#include "../minishell.h"

int	ft_check_between_pipes(t_data *data)
{
	t_lexer	*lexer_clone;
	int		num = 0;

	lexer_clone = data->lst_lexer;
	data->error = 0;
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
				break;
			if (lexer_clone->type == PIPE && num == 0)
			{
				printf("Syntax error near unexpected token `|'\n");
				data->error = 258;
				break;
			}
		}
		if (lexer_clone->type != PIPE)
			lexer_clone = lexer_clone->next;
	}
	return (data->error);
}