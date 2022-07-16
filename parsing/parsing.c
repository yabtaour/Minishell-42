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
	int		mamak = 0;

	lexer_clone = data->lst_lexer;
	while(lexer_clone && i < position)
	{
		i++;
		mamak++;
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
	if (!mamak)
		data->lst_lexer = lexer_clone;
}

int	ft_check_still_redirection(t_data *data)
{
	t_lexer	*lexer_clone;

	lexer_clone = data->lst_lexer;
	while (lexer_clone && lexer_clone->type != PIPE)
	{
		if (lexer_clone->type == REDIRECTION)
			return (1);
		lexer_clone = lexer_clone->next;
	}
	return (0);
}

void	ft_delete_redirections(t_data *data)
{
	t_lexer	*lexer_clone;
	t_lexer	*lexer_clone2;
	int		delete = 0;
	int		position;

	lexer_clone = data->lst_lexer;
	while (ft_check_still_redirection(data))
	{
		position = 0;
		while (lexer_clone && lexer_clone->type != PIPE)
		{
			if (lexer_clone && lexer_clone->type == REDIRECTION)
			{
				position++;
				lexer_clone = lexer_clone->next;
				while (lexer_clone && lexer_clone->type == SPACE)
				{
					position++;
					lexer_clone = lexer_clone->next;
				}
				while (lexer_clone && lexer_clone->type != REDIRECTION)
				{
					ft_delete_node_red(data, position);
					position--;
					lexer_clone = lexer_clone->prev;
				}
				if (lexer_clone)
					ft_delete_node_red(data, position);
			}
			position++;
			if (lexer_clone)
				lexer_clone = lexer_clone->next;
		}
		lexer_clone = data->lst_lexer;
		position = 0;
		while (lexer_clone && lexer_clone->type != PIPE)
		{
			if (lexer_clone && lexer_clone->type == REDIRECTION)
				ft_delete_node_red(data, position);
			position++;
			lexer_clone = lexer_clone->next;
		}
		lexer_clone = data->lst_lexer;
	}
}

t_cmd	*ft_create_new_command(char *command, int fd_in, int fd_out)
{
	t_cmd	*cmd;
	char	**all_cmd;

	cmd = malloc(sizeof(t_cmd));
	all_cmd = ft_new_split(command, ' ');
	cmd->cmd = all_cmd;
	cmd->fd_in = fd_in;
	cmd->fd_out = fd_out;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

t_cmd	*ft_add_back_cmd(t_data *data, int *fd, int *red, int red_num)
{
	int		fd_in = 0;
	int		fd_out = 0;
	int		i = 0;
	t_lexer	*lexer_clone;
	t_cmd	*node;
	t_cmd	*cmd_clone;
	char	*command = NULL;

	lexer_clone = data->lst_lexer;
	while (lexer_clone && lexer_clone->type != PIPE)
	{
		command = ft_strjoin(command, lexer_clone->value);
		command = ft_strjoin(command, " ");
		lexer_clone = lexer_clone->next;
	}
	while (i < red_num)
	{
		if (red[i] == 1 || red[i] == 2)
			fd_out = fd[i];
		else if (red[i] == 3)
			fd_in = fd[i];
		i++;
	}
	node = ft_create_new_command(command, fd_in, fd_out);
	free(command);
	if (!data->lst_cmd)
		return (node);
	cmd_clone = data->lst_cmd;
	while (cmd_clone->next)
		cmd_clone = cmd_clone->next;
	cmd_clone->next = node;
	node->prev = cmd_clone;
	return (data->lst_cmd);
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
			while (lexer_clone->type == SPACE)
				lexer_clone = lexer_clone->next;
			if (lexer_clone)
			{
				if (red[i] == 1)
					fd[i] = open(lexer_clone->value, O_RDWR | O_CREAT | O_TRUNC, 0777);
				if (red[i] == 2)
					fd[i] = open(lexer_clone->value, O_RDWR | O_CREAT | O_APPEND | O_RDWR, 0777);
				if (red[i] == 3)
					fd[i] = open(lexer_clone->value, O_RDONLY, 0777);
				i++;
			}
		}
		lexer_clone = lexer_clone->next;
	}
	ft_delete_redirections(data);
	data->lst_cmd = ft_add_back_cmd(data, fd, red, red_num);
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
			// if (lexer_clone->type == DOUBLE_QUOTES || lexer_clone->type == SINGLE_QUOTES)
			// 	data->eof[i++] = ft_substr(lexer_clone->value, 1, strlen(lexer_clone->value) - 2);
			// else
			// 	data->eof[i++] = ft_substr(lexer_clone->value, 0, strlen(lexer_clone->value));			
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

void	ft_add_command_pipe(t_data *data)
{
	t_lexer	*lexer_clone;

	while (data->lst_lexer)
		ft_add_normal_command(data);
}

void	ft_parsing(t_data *data)
{
	ft_handle_herdoc(data);
	ft_add_command_pipe(data);
}