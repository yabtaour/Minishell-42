#include "../minishell.h"

static int	ft_check_pipe(t_data *data)
{
	t_lexer	*lexer_clone;

	lexer_clone = data->lst_lexer;
	while (lexer_clone)
	{
		if (lexer_clone->type == PIPE)
			return (1);
		lexer_clone = lexer_clone->next;
	}
	return (0);
}

int	ft_check_still_redirection(t_data *data)
{
	t_lexer	*lexer_clone;

	lexer_clone = data->lst_lexer;
	while (lexer_clone && lexer_clone->type != PIPE)
	{
		if (lexer_clone->type == REDIRECTION
			&& ft_strcmp(lexer_clone->value, "<<"))
			return (1);
		lexer_clone = lexer_clone->next;
	}
	return (0);
}

void	ft_add_normal_command(t_data *data)
{
	int		*red;
	int		red_num;
	t_lexer	*lexer_clone;
	int		*fd;
	int		i;

	i = 0;
	red_num = ft_red_num(data);
	red = ft_fill_red(data, red_num);
	fd = malloc (sizeof(int) * red_num);
	lexer_clone = data->lst_lexer;
	while (lexer_clone && lexer_clone->type != PIPE)
	{
		if (lexer_clone->type == REDIRECTION
			&& ft_strcmp(lexer_clone->value, "<<"))
		{
			lexer_clone = lexer_clone->next;
			fd[i] = ft_fill_fd(data, lexer_clone->value, red[i]);
			i++;
		}
		lexer_clone = lexer_clone->next;
	}
	ft_delete_redirections(data);
	data->lst_cmd = ft_add_back_cmd(data, fd, red, red_num);
}

int	ft_check_still_pipe(t_data *data)
{
	t_lexer	*lexer_clone;

	lexer_clone = data->lst_lexer;
	while (lexer_clone)
	{
		if ((lexer_clone) || lexer_clone->type == PIPE)
			return (1);
		lexer_clone = lexer_clone->next;
	}
	return (0);
}

void	ft_parsing(t_data *data)
{
	ft_handle_herdoc(data);
	ft_add_command_pipe(data);
}
