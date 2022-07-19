#include "../minishell.h"

int	ft_len_before(char *var)
{
	int	len = 0;
	int	flag_d;
	int	flag_s;

	flag_d = 0;
	flag_s = 0;
	while (flag_s == 1 || (var[len] && var[len] != '$'))
	{
		if (var[len] == '"' && flag_s == 0)
			flag_d = ft_change_flag(flag_d);
		if (var[len] == '\'' && flag_d == 0)
			flag_s = ft_change_flag(flag_s);
		len++;
	}
	return (len);
}

int	ft_len_after(char *var)
{
	int	len = 0;
	int	i = 0;
	int	flag_d = 0;
	int	flag_s = 0;

	flag_s = 0;
	flag_d = 0;
	while (flag_s == 1 || (var[i] && var[i] != '$'))
	{
		if (var[i] == '"' && flag_s == 0)
			flag_d = ft_change_flag(flag_d);
		if (var[i] == '\'' && flag_d == 0)
			flag_s = ft_change_flag(flag_s);
		i++;
	}
	if (var[i] && var[i] == '$')
	{
		i++;
		while (var[i] && var[i] != ' ' && var[i] != '$'
			&& var[i] != '\\' && var[i] != '"' && var[i] != '\'' && var[i] != '=')
				i++;
		if (var[i])
		{
			while (var[i++])
				len++;
		}
	}
	return (len);
}

int	ft_len_var(char *var)
{
	int	i = 0;
	int	len = 0;
	int	flag_s = 0;
	int	flag_d = 0;

	while (flag_s == 1 || (var[i] && var[i] != '$'))
	{
		if (var[i] == '"' && flag_s == 0)
			flag_d = ft_change_flag(flag_d);
		if (var[i] == '\'' && flag_d == 0)
			flag_s = ft_change_flag(flag_s);
		i++;
	}
	if (flag_s == 0)
	{
		if (var[i] && var[i] == '$')
		{
			i++;
			while (var[i] && var[i] != ' ' && var[i] != '$' && var[i] != '\''
				&& var[i] != '\\' && var[i] != '"' && var[i] != '=')
			{
				i++;
				len++;
			}
		}
	}
	return (len);
}