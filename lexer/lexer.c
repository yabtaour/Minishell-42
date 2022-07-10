#include "../minishell.h"

//had lfunction kachecki quotes w katb9a ghada 7ta katl9aha tsddat
//then kat7tt dakchi kaml fnode w7da

int		ft_double_single(t_data *data, int i, int type)
{
	char	*str;
	int		len;
	int		origin;
	char	c;
	int		flag = 0;

	len = 0;
	origin = i;
	if (type == DOUBLE_QUOTES)
		c = '"';
	else
		c = '\'';
	while (data->cmd[i++] != '\0')
	{
		if (data->cmd[i + 1] == ' ')
			flag = 1;
		len++;
		if ((data->cmd[i] == c && flag == 1) || data->cmd[i] == '\'')
			break ;
	}
	str = malloc (len + 2);
	i = 1;
	str[0] = c;
	flag = 0;
	origin++;
	while ((data->cmd[origin]) != '\0')
	{
		if (data->cmd[origin + 1] == ' ')
			flag = 1;
		str[i] = data->cmd[origin];
		origin++;
		if (str[i] == c && flag == 1)
			break ;
		i++;
	}
	i++;
	str[i] = '\0';
	data->lst_lexer = ft_add_lexer_back(data->lst_lexer, str, type);
	return (origin); 
}

/// had lfunction katchouf type dyal lcaracter li wslt lih mn lcommand li dkhlti
/// then kat3yt lfunction li katchecki dakchi li morah



void	ft_lexer(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmd[i])
	{
		if (ft_isalpha(data->cmd[i]) || ft_isdigit(data->cmd[i]))
			i = ft_add_token(data, i, WORD);
		else if (data->cmd[i] == '|')
			i = ft_add_token(data, i, PIPE);
		else if (data->cmd[i] == ';')
			i = ft_add_token(data, i, SEMI);
		else if (data->cmd[i] == ' ')
			i = ft_add_token(data, i, SPACE);
		else if (data->cmd[i] == '"')
			i = ft_double_single(data, i, DOUBLE_QUOTES);
		else if (data->cmd[i] == '\'')
			i = ft_double_single(data, i, SINGLE_QUOTES);
		else if(ft_is_operation(data->cmd[i]))
			i = ft_add_token(data, i, OPERATION);
		else if (ft_is_curly(data->cmd[i]))
			i = ft_add_token(data, i, WORD);
		else if (ft_is_straight(data->cmd[i]))
			i = ft_add_token(data, i, PARENTHESIS);
		else if (ft_is_redirection(data->cmd[i]))
			i = ft_add_token(data, i, REDIRECTION);
		else if (data->cmd[i] == '-')
			i = ft_add_token(data, i, MINUS);
		else if (data->cmd[i] == '=')
			i = ft_add_token(data, i , EQUAL);
		else if (data->cmd[i] == '&')
			i = ft_add_token(data, i, AND);
		else if (data->cmd[i] == '$')
			i = ft_add_token(data, i, DOLLAR);
		else if (data->cmd[i] == '.')
			i = ft_add_token(data, i, POINT);
		else
			i++;
	}
}