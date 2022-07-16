#include "minishell.h"

char	*ft_trim(char *str)
{
	int		i;
	char	*result = NULL;
	int		j;
	int		end;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while(str[i] == ' ')
		i++;
	if (str[i])
	{
		while (str[i])
		{
			j++;
			i++;
		}
		i--;
		while (str[i] == ' ')
		{
			i--;
			j++;
		}
		end = i;
		result = malloc (j + 1);
		i = 0;
		j = 0;
		while (str[i] == ' ')
			i++;
		while (i <= end)
		{
			result[j] = str[i];
			i++;
			j++;
		}
		result[j] = '\0';
		free(str);
		return (result);
	}
	return (str);
}

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
	int	flag_d = 0;
	int	flag_s = 0;
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
	printf("%s\n", new_cmd);
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

	cmd_clone = data->lst_cmd;
	while (cmd_clone)
	{
			while (cmd_clone->cmd[i])
			{
				if (ft_exist_quotes(cmd_clone->cmd[i]))
				{
					HERE
					temp = ft_substr(cmd_clone->cmd[i], 0, strlen(cmd_clone->cmd[i]));
					HERE
					free(cmd_clone->cmd[i]);
					HERE
					printf("%s\n", ft_delete(cmd_clone->cmd[i]));
					// cmd_clone->cmd[i] = strcpy(cmd_clone->cmd[i], ft_delete(cmd_clone->cmd[i]));
					HERE
					printf("%s\n", cmd_clone->cmd[i]);
					i++;
				}
			}
		cmd_clone = cmd_clone->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	data.ac = argc;
	data.av = argv;
	data.env = env;
	data.first_export = NULL;
	ft_env(&data);
	while (69)
	{
		data.lst_lexer = NULL;
		data.lst_cmd = NULL;
		data.error = 0;
		data.cmd = readline("minishell-1.0 > ");
		if (!data.cmd || !strcmp(data.cmd, "exit"))
			exit(1);
		if (data.cmd && data.cmd[0] != '\n')
		{
			data.cmd = ft_trim(data.cmd);
			add_history(data.cmd);
			ft_lexer(&data);
			free(data.cmd);
			data.error = ft_syntax_analyzer(&data);
			if (data.error)
			{
				ft_free_lexer(data.lst_lexer);
				continue;
			}
			HERE
			ft_expanding(&data);
			HERE
			ft_print_lexer(data.lst_lexer);
			HERE
			ft_parsing(&data);
			HERE
			ft_print_lexer(data.lst_lexer);
			HERE
			// ft_delete_quotes(&data);
			HERE
			ft_print_cmd(data.lst_cmd);
			if (data.lst_cmd)
				echo(&data, data.lst_cmd, data.lst_cmd->fd_in);
			cd(&data, data.lst_cmd);
			pwd(&data, data.lst_cmd, 1);
			ft_print_lexer(data.lst_lexer);
			unset(&data, "zzz");
			printf("%d\n", export(&data, data.lst_cmd, 1));
			exe(&data);
			ft_free_lexer(data.lst_lexer);
			ft_free_cmd(data.lst_cmd);
		}
	}
	return (0);
}

// /Users/yabtaour/Desktop/Minishell