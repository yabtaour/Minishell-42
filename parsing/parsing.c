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

void	ft_delete_node_red(t_data *data, int position)
{
	t_lexer	*lexer_clone;
	t_lexer	*lexer_clone2;
	int		i  = 0;

	lexer_clone = data->lst_lexer;
	while(lexer_clone && i < position)
	{
		i++;
		lexer_clone = lexer_clone->next;
	}
	if (lexer_clone)
	{
		if (lexer_clone && lexer_clone->next)
			lexer_clone->next->prev  = lexer_clone->prev;
		if (lexer_clone && lexer_clone->prev)
			lexer_clone->prev->next = lexer_clone->next;
		lexer_clone2 = lexer_clone->next;
		free(lexer_clone);
		lexer_clone = lexer_clone2;
	}
	if (!i)
		data->lst_lexer = lexer_clone;
}

int	ft_check_still_redirection(t_data *data)
{
	t_lexer	*lexer_clone;

	lexer_clone = data->lst_lexer;
	while (lexer_clone && lexer_clone->type != PIPE)
	{
		if (lexer_clone->type == REDIRECTION && strcmp(lexer_clone->value, "<<"))
			return (1);
		lexer_clone = lexer_clone->next;
	}
	return (0);
}

void	ft_delete_redirections(t_data *data)
{
	t_lexer	*lexer_clone;
	t_lexer	*lexer_clone2;
	int		position;
	int		flag;

	lexer_clone = data->lst_lexer;
	while (ft_check_still_redirection(data))
	{
		position = 0;
		while (lexer_clone && lexer_clone->type != PIPE)
		{
			flag = 0;
			if (lexer_clone && lexer_clone->type == REDIRECTION && strcmp(lexer_clone->value, "<<"))
			{
				flag = 1;
				position++;
				lexer_clone = lexer_clone->next;
				while (lexer_clone && lexer_clone->type != REDIRECTION)
				{
					ft_delete_node_red(data, position);
					position--;
					lexer_clone = lexer_clone->prev;
				}
				if (lexer_clone)
					ft_delete_node_red(data, position);
			}
			if (!flag)
				position++;
			if (lexer_clone)
				lexer_clone = lexer_clone->next;
		}
		lexer_clone = data->lst_lexer;
		position = 0;
		while (lexer_clone && lexer_clone->type != PIPE)
		{
			if (lexer_clone && lexer_clone->type == REDIRECTION && strcmp(lexer_clone->value, "<<"))
				ft_delete_node_red(data, position);
			position++;
			lexer_clone = lexer_clone->next;
		}
		lexer_clone = data->lst_lexer;
	}
}

void	ft_delete_command(t_data *data)
{
	t_lexer	*lexer_clone;

	lexer_clone = data->lst_lexer;

	while (lexer_clone && lexer_clone->type != PIPE)
	{
		if (lexer_clone->next)
			lexer_clone->next->prev = lexer_clone->prev;
		if (lexer_clone->prev)
			lexer_clone->prev->next = lexer_clone->next;
		data->lst_lexer = lexer_clone->next;
		free(lexer_clone);
		lexer_clone = data->lst_lexer;
	}
	if (lexer_clone)
	{
		if (lexer_clone->next)
			lexer_clone->next->prev = lexer_clone->prev;
		if (lexer_clone->prev)
			lexer_clone->prev->next = lexer_clone->next;
		data->lst_lexer = lexer_clone->next;
		free(lexer_clone);
		lexer_clone = data->lst_lexer;
	}
}

void	ft_delete_herdoc(t_data *data)
{
	t_cmd	*cmd_clone;
	char	**new_cmd;
	int		len;
	int		i;

	cmd_clone = data->lst_cmd;
	while (cmd_clone->next)
		cmd_clone = cmd_clone->next;
	if (cmd_clone->her_doc_num)
	{
		i = 1;
		while (cmd_clone->cmd && cmd_clone->cmd[i])
			i++;
		new_cmd = malloc (sizeof(char *) * (i - (cmd_clone->her_doc_num * 2) + 1));
		len = 0;
		i = 0;
		while (cmd_clone->cmd && cmd_clone->cmd[i])
		{
			if (!strcmp(cmd_clone->cmd[i], "<<"))
				i += 2;
			else
			{
				new_cmd[len] = ft_substr(cmd_clone->cmd[i], 0, strlen(cmd_clone->cmd[i]));
				len++;
				i++;
			}
		}
		new_cmd[len] = NULL;
		i = 0;
		free_split(cmd_clone->cmd);
		i = 0;
		while (new_cmd && new_cmd[i])
			i++;
		cmd_clone->cmd = malloc (sizeof (char *) * i + 1);
		i = 0;
		while (new_cmd && new_cmd[i])
		{
			cmd_clone->cmd[i] = ft_substr(new_cmd[i], 0, strlen(new_cmd[i]));
			i++;
		}
		cmd_clone->cmd[i] = NULL;
	}		
}

void	ft_add_normal_command(t_data *data)
{
	t_lexer	*lexer_clone;
	int		*red;
	int		*fd;
	int		red_num = 0;
	int		i = 0;

	lexer_clone = data->lst_lexer;	
	while (lexer_clone && lexer_clone->type != PIPE)
	{		
		if (lexer_clone->type == REDIRECTION && strcmp(lexer_clone->value, "<<"))
			red_num++;
		lexer_clone = lexer_clone->next;
	}
	red = malloc (sizeof(int) * red_num);
	fd = malloc (sizeof(int) * red_num);
	lexer_clone = data->lst_lexer;
	while (lexer_clone && lexer_clone->type != PIPE)
	{
		if (strcmp(lexer_clone->value, ">") == 0)
			red[i++] = 1;
		if (strcmp(lexer_clone->value, ">>") == 0)
			red[i++] = 2;
		if (strcmp(lexer_clone->value, "<") == 0)
			red[i++] = 3;
		lexer_clone = lexer_clone->next;
	}
	i = 0;
	lexer_clone = data->lst_lexer;
	while (lexer_clone && lexer_clone->type != PIPE)
	{
		if (lexer_clone->type == REDIRECTION && strcmp(lexer_clone->value, "<<"))
		{
			lexer_clone = lexer_clone->next;
			if (lexer_clone)
			{
				if (red[i] == 1)
					fd[i] = open(lexer_clone->value, O_RDWR | O_CREAT | O_TRUNC, 0664);
				if (red[i] == 2)
					fd[i] = open(lexer_clone->value, O_RDWR | O_CREAT | O_APPEND, 0664);
				if (red[i] == 3)
				{
					fd[i] = open(lexer_clone->value, O_RDONLY, 0777);
					if (fd[i] == -1)
					{
						printf("No such file or directory\n");
						data->error = 1;
						fd[i] = -69;
					}
				}
				i++;
			}
		}
		lexer_clone = lexer_clone->next;
	}
	ft_delete_redirections(data);
	data->lst_cmd = ft_add_back_cmd(data, fd, red, red_num);
	ft_delete_herdoc(data);
	ft_delete_command(data);
}

void	ft_handle_herdoc(t_data *data)
{
	t_lexer	*lexer_clone;
	int		i;

	i = 0;
	lexer_clone = data->lst_lexer;
	while (lexer_clone)
	{
		if (strcmp(lexer_clone->value, "<<") == 0)
			data->her_doc++;
		lexer_clone = lexer_clone->next;
	}
	data->eof = malloc(sizeof(char *) * data->her_doc + 1);
	lexer_clone = data->lst_lexer;
	while (lexer_clone)
	{
		if (strcmp(lexer_clone->value, "<<") == 0)
		{
			lexer_clone = lexer_clone->next;
			data->eof[i] = ft_substr(lexer_clone->value, 0, strlen(lexer_clone->value));
			ft_delete_eof_quotes(data->eof[i]);
			i++;		
		}
		lexer_clone = lexer_clone->next;
	}
	data->eof[i] = NULL;
}

int		ft_check_still_pipe(t_data *data)
{
	t_lexer *lexer_clone;

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
	// ft_print_lexer(data->lst_lexer);
	ft_handle_herdoc(data);
	ft_add_command_pipe(data);
}