#include "../minishell.h"

int	ft_is_parenth(char c)
{
	if (c == '{' || c == '}'
		|| c == '(' || c == ')')
		return (1);
	return (0);
}

int	ft_is_redirection(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	ft_is_word(char c)
{
	if (c != '|' && c != '&' && !ft_is_redirection(c)
		&& c != ' ' && c != ';' && !ft_is_parenth(c))
		return (1);
	return (0);
}
