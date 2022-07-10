#include "../minishell.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c <= 'Z' && c >= 'A')
		|| c == '{' || c == '}')
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_is_operation(int c)
{
	if (c == '+'
		|| c == '*' || c == '/')
		return (1);
	return (0);
}

int	ft_is_curly(int c)
{
	if (c == '{' || c == '}')
		return (1);
	return (0);
}

int ft_is_straight(int c)
{
	if (c == '(' || c == ')')
		return (1);
	return (0);
}

int	ft_is_redirection(int c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	ft_check_after_minus(int c)
{
	if (c == '-' || ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

int	ft_is_right(int c, int type)
{
	if (c != '\0' && (((ft_isalpha(c) || ft_isdigit(c)) && type == WORD)
		|| (c == '|' && type == PIPE)
		|| (c == ' ' && type == SPACE)
		|| (c != ' ' && type == OPERATION)
		|| ((ft_isalpha(c) || ft_isdigit(c)) && type == CURLY_BRACKET)
		|| (ft_is_straight(c) && type == PARENTHESIS)
		|| (ft_is_redirection(c) && type == REDIRECTION)
		|| ((c != ' ') && type == DOLLAR)
		|| (c == '&' && type == AND)
		|| (ft_check_after_minus(c) && type == MINUS)
		|| (c != ' ' && c!= '"' && type == EQUAL)
		|| (c == '.' && type == POINT)
		|| (c == ';' && type == SEMI)))
		return (1);
	return (0);
}

int	ft_word_len(char *word, int	i, int type)
{
	int	len;

	len = 0;
	while(ft_is_right(word[len], type))
	{
		len++;
		i++;
	}
	return (len);
}