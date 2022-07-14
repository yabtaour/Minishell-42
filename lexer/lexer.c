#include "../minishell.h"

//had lfunction kachecki quotes w katb9a ghada 7ta katl9aha tsddat
//then kat7tt dakchi kaml fnode w7da

// int		ft_double_single(t_data *data, int i, int type)
// {
// 	char	*str;
// 	int		len;
// 	int		origin;
// 	char	c;
// 	int		flag = 0;

// 	len = 0;
// 	origin = i;
// 	if (type == DOUBLE_QUOTES)
// 		c = '"';
// 	else
// 		c = '\'';
// 	while (data->cmd[i++] != '\0')
// 	{
// 		if (data->cmd[i + 1] == ' ')
// 			flag = 1;
// 		len++;
// 		if ((data->cmd[i] == c && flag == 1) || data->cmd[i] == '\'')
// 			break ;
// 	}
// 	str = malloc (len + 2);
// 	i = 1;
// 	str[0] = c;
// 	flag = 0;
// 	origin++;
// 	while ((data->cmd[origin]) != '\0')
// 	{
// 		if (data->cmd[origin + 1] == ' ')
// 			flag = 1;
// 		str[i] = data->cmd[origin];
// 		origin++;
// 		if (str[i] == c && flag == 1)
// 			break ;
// 		i++;
// 	}
// 	i++;
// 	str[i] = '\0';
// 	data->lst_lexer = ft_add_lexer_back(data->lst_lexer, str, type);
// 	return (origin); 
// }

// /// had lfunction katchouf type dyal lcaracter li wslt lih mn lcommand li dkhlti
// /// then kat3yt lfunction li katchecki dakchi li morah



// void	ft_lexer(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (data->cmd[i])
// 	{
// 		if (ft_isalpha(data->cmd[i]) || ft_isdigit(data->cmd[i]))
// 			i = ft_add_token(data, i, WORD);
// 		else if (data->cmd[i] == '|')
// 			i = ft_add_token(data, i, PIPE);
// 		else if (data->cmd[i] == ';')
// 			i = ft_add_token(data, i, SEMI);
// 		else if (data->cmd[i] == ' ')
// 			i = ft_add_token(data, i, SPACE);
// 		else if (data->cmd[i] == '"')
// 			i = ft_double_single(data, i, DOUBLE_QUOTES);
// 		else if (data->cmd[i] == '\'')
// 			i = ft_double_single(data, i, SINGLE_QUOTES);
// 		else if(ft_is_operation(data->cmd[i]))
// 			i = ft_add_token(data, i, OPERATION);
// 		else if (ft_is_curly(data->cmd[i]))
// 			i = ft_add_token(data, i, WORD);
// 		else if (ft_is_straight(data->cmd[i]))
// 			i = ft_add_token(data, i, PARENTHESIS);
// 		else if (ft_is_redirection(data->cmd[i]))
// 			i = ft_add_token(data, i, REDIRECTION);
// 		else if (data->cmd[i] == '-')
// 			i = ft_add_token(data, i, MINUS);
// 		else if (data->cmd[i] == '=')
// 			i = ft_add_token(data, i , EQUAL);
// 		else if (data->cmd[i] == '&')
// 			i = ft_add_token(data, i, AND);
// 		else if (data->cmd[i] == '$')
// 			i = ft_add_token(data, i, DOLLAR);
// 		else if (data->cmd[i] == '.')
// 			i = ft_add_token(data, i, POINT);
// 		else
// 			i++;
// 	}
// }

int	ft_is_word(char c)
{
	if (c != '|' && c != '&' && !ft_is_redirection(c) && c != ' ')
		return (1);
	return (0);
}

int	ft_add_word(t_data *data, int i)
{
	int		len = 0;
	char	c;
	int		origin;
	char	*command = NULL;
	int		flag_s = 0;
	int		flag_d = 0;

	origin = i;
	while (data->cmd[i] && ft_is_word(data->cmd[i]))
	{
		if (data->cmd[i] == '"' || data->cmd[i] == '\'')
		{
			c = data->cmd[i];
			i++;
			len++;
			while (data->cmd[i] && data->cmd[i] != c)
			{
				i++;
				len++;
			}
		}
		len++;
		i++;
	}
	command = malloc (sizeof(char) * len + 1);
	len = 0;
	while (data->cmd[origin] && ft_is_word(data->cmd[origin]))
	{
		if (data->cmd[origin] == '"' || data->cmd[origin] == '\'')
		{
			c = data->cmd[origin];
			command[len] = data->cmd[origin];
			origin++;
			len++;
			while (data->cmd[origin] && data->cmd[origin] != c)
			{
				command[len] = data->cmd[origin];
				origin++;
				len++;
			}
		}
		command[len] = data->cmd[origin];
		len++;
		origin++;
	}
	command[len] = '\0';
	data->lst_lexer = ft_add_lexer_back(data->lst_lexer, command, WORD);
	ft_print_lexer(data->lst_lexer);
	free(command);
	return (i);
}

int	ft_add_and(t_data *data, int i)
{
	int		origin = i;
	int		len = 0;
	char	*command = NULL;
	
	while (data->cmd[i] && data->cmd[i] == '&')
	{
		i++;
		len++;
	}
	command = malloc(sizeof(char) * len + 1);
	if (!command)
	{
		HERE
		exit(1);
	}
	len = 0;
	while (data->cmd[origin] && data->cmd[origin] == '&')
	{
		command[len] = data->cmd[origin];
		origin++;
		len++;
	}
	command[len] = '\0';
	data->lst_lexer = ft_add_lexer_back(data->lst_lexer, command, AND);
	ft_print_lexer(data->lst_lexer);	
	return (i);
}

int	ft_add_redirection(t_data *data, int i)
{
	char	*command = NULL;
	int		len;
	int		origin;

	origin = i;
	while (data->cmd[i] && ft_is_redirection(data->cmd[i]))
	{
		i++;
		len++;
	}
	command = malloc(sizeof(char) * len + 1);
	if (!command)
	{
		HERE
		exit(1);
	}
	len = 0;
	while (data->cmd[origin] && ft_is_redirection(data->cmd[origin]))
	{
		command[len] = data->cmd[origin];
		len++;
		origin++;
	}
	command[len] = '\0';
	data->lst_lexer = ft_add_lexer_back(data->lst_lexer, command, 3);
	ft_print_lexer(data->lst_lexer);
	free(command);
	return (i);
}

int	ft_add_pipe(t_data *data, int i)
{
	int		origin = i;
	char	*command = NULL;
	int		len = 0;

	while (data->cmd[i] && data->cmd[i] == '|')
	{
		i++;
		len++;
	}
	command = malloc (sizeof(char) * len + 1);
	if (!command)
	{
		HERE
		exit (1);
	}
	len = 0;
	while (data->cmd[origin] && data->cmd[origin] == '|')
	{
		command[len] = data->cmd[origin];
		origin++;
		len++;
	}
	command[len] = '\0';
	ft_add_lexer_back(data->lst_lexer, command, PIPE);
	free(command);
	return (i);
}

void	ft_lexer(t_data *data)
{
	int		i = 0;

	while (data->cmd[i])
	{
		while (data->cmd[i] == ' ')
			i++;
		if (data->cmd[i] != '&' && data->cmd[i] != '|'
			&& !ft_is_redirection(data->cmd[i]))
			i = ft_add_word(data, i);
		if (ft_is_redirection(data->cmd[i]))
			i = ft_add_redirection(data, i);
		if (data->cmd[i] == '&')
			i = ft_add_and(data, i);
		if (data->cmd[i] == '|')
			i = ft_add_pipe(data, i);
	}
}