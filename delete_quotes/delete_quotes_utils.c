#include "../minishell.h"

int	ft_real_len(char *cmd)
{
	int	len;
	int	flag_d;
	int	flag_s;
	int	i;

	i = 0;
	len = 0;
	flag_d = 0;
	flag_d = 0;
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

int	ft_len(char *cmd)
{
	int	i;
	int	flag_s;
	int	flag_d;
	int	len;

	i = 0;
	flag_d = 0;
	flag_s = 0;
	len = 0;
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

int	*ft_fill_index(int *index, char *cmd)
{
	int	i;
	int	len;
	int	flag_d;
	int	flag_s;

	i = -1;
	len = 0;
	flag_d = 0;
	flag_s = 0;
	while (cmd[++i])
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
	}
	return (index);
}

int	*ft_get_index(char *cmd, int type)
{
	int		*index;

	index = NULL;
	if (type == 1)
	{
		index = malloc (sizeof(int) * ft_len(cmd));
		index = ft_fill_index(index, cmd);
	}
	return (index);
}
