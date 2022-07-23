#include "../minishell.h"

int	ft_len_before(char *var)
{
	int	len;
	int	flag_d;
	int	flag_s;

	flag_d = 0;
	flag_s = 0;
	len = 0;
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

int	ft_skip(char *value, int i)
{
	i++;
	while (value[i] && value[i] != ' ' && value[i] != '$'
		&& value[i] != '\\' && value[i] != '\''
		&& value[i] != '"' && value[i] != '=')
		i++;
	return (i);
}

int	ft_len_after(char *var)
{
	int	len;
	int	i;
	int	flag_d;
	int	flag_s;

	flag_s = 0;
	flag_d = 0;
	i = 0;
	len = 0;
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
		i = ft_skip(var, i);
		while (var[i++])
			len++;
	}
	return (len);
}

int	ft_calculate_len(char *value, int i)
{
	int	len;

	len = 0;
	i++;
	while (value[i] && value[i] != ' ' && value[i] != '$'
		&& value[i] != '\\' && value[i] != '\''
		&& value[i] != '"' && value[i] != '=')
	{
		i++;
		len++;
	}
	return (len);
}

int	ft_len_var(char *var)
{
	int	i;
	int	len;
	int	flag_s;
	int	flag_d;

	flag_s = 0;
	flag_d = 0;
	i = 0;
	len = 0;
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
			len = ft_calculate_len(var, i);
	}
	return (len);
}
