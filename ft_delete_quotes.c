#include "./minishell.h"

int	ft_real_len(char *cmd)
{
	int	len = 0;
	int	flag_d = 0;
	int	flag_s = 0;
	int	i = 0;

	while (cmd[i])
	{
		if (cmd[i] == '"' && flag_s == 0)
		{
			len++;
			flag_d = ft_change_flag(flag_d);
		}
		if (cmd[i] == '\'' && flag_d == 0)
		{
			len++;
			flag_s = ft_change_flag(flag_s);
		}
		i++;
	}
	return (len);
}

int	*ft_get_index(char *cmd, int type)
{
	int		i = 0;
	char	c;
	int		len = 0;
	int		flag_d = 0;
	int		flag_s = 0;
	int		*index;

	if (type == 1)
	{
		while (cmd[i])
		{
			if (cmd[i] == '"' && flag_s == 0)
			{
				len++;
				flag_d = ft_change_flag(flag_d);
			}
			if (cmd[i] == '\'' && flag_d == 0)
			{
				len++;
				flag_s = ft_change_flag(flag_s);
			}
			i++;			
		}
		index = malloc (sizeof(int) * len);
		len = 0;
		i = 0;
		while (cmd[i])
		{
			if (cmd[i] == '"' && flag_s == 0)
			{
				index[len] = i;
				len++;
				flag_d = ft_change_flag(flag_d);
			}
			if (cmd[i] == '\'' && flag_d == 0)
			{
				index[len] = i;
				len++;
				flag_s = ft_change_flag(flag_s);
			}
			i++;		
		}
	}
	return (index);
}

int	ft_exist(int i, int *index, int len)
{
	int	idx = 0;

	while (idx < len)
	{
		if (index[idx] == i)
			return (1);
		idx++;
	}
	return (0);
}

char	*ft_delete(char *cmd)
{
	int		*index;
	int		i = 0;
	int		len = 0;
	int		r = 0;
	char	*new_cmd;

	index = ft_get_index(cmd, 1);
	r = ft_real_len(cmd);
	new_cmd = malloc (strlen(cmd) + 1 - r);
	while (cmd[i])
	{
		if (!ft_exist(i, index, r))
		{
			new_cmd[len] = cmd[i];
			len++;
		}
		i++;
	}
	new_cmd[len] = '\0';
	free(index);
	return (new_cmd);
}

int	ft_exist_quotes(char *cmd)
{
	int	i = 0;

	while (cmd[i])
	{
		if (cmd[i] == '"' || cmd[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

void	ft_delete_quotes(t_data *data)
{
	t_cmd	*cmd_clone;
	int		r_len = 0;
	char	*temp = NULL;
	int		i = 0;
	int		j = 0;

	ft_print_cmd(data->lst_cmd);
	cmd_clone = data->lst_cmd;
	while (cmd_clone && cmd_clone->cmd)
	{
		i = 0;
		while (cmd_clone->cmd[i])
		{
			if (ft_exist_quotes(cmd_clone->cmd[i]))
			{
				temp = ft_substr(cmd_clone->cmd[i], 0, strlen(cmd_clone->cmd[i]));
				free(cmd_clone->cmd[i]);
				cmd_clone->cmd[i] = ft_substr(ft_delete(temp), 0, strlen(temp));
				free(temp);
			}
			i++;
		}
		cmd_clone = cmd_clone->next;
	}
}

void	ft_delete_eof_quotes(char *eof)
{
	char	*temp = NULL;

	if (ft_exist_quotes(eof))
	{
		temp = ft_substr(eof, 0, strlen(eof));
		free(eof);
		eof = ft_substr(ft_delete(temp), 0, strlen(temp));
		free(temp);
	}
}