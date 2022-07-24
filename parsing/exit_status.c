#include "../minishell.h"

char	*ft_new_value(t_data *data, char *value)
{
	char	*exit_s;
	int		len;
	char	*new_value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	exit_s = ft_itoa(data->general.old_error);
	len = ft_strlen(exit_s) + ft_strlen(value) - 2;
	new_value = malloc(sizeof(char) * len + 1);
	while (value[i])
	{
		if (value[i] == '$' && value[i + 1] == '?')
		{
			new_value = ft_strjoin(new_value, exit_s);
			j += ft_strlen(exit_s);
			i += 2;
		}
		else
		{
			new_value[j] = value[i];
			j++;
			i++;
		}
	}
	new_value[j] = '\0';
	return (new_value);
}

char	*ft_change_value(t_data *data, char *value)
{
	char	*temp;

	temp = ft_substr(value, 0, ft_strlen(value));
	free(value);
	value = ft_new_value(data, temp);
	free(temp);
	printf("%s\n", value);
	return (value);
}

void	ft_change_exit_status(t_data *data)
{
	t_lexer	*lexer_clone;
	int		i;

	lexer_clone = data->lst_lexer;
	while (lexer_clone)
	{
		data->flag_d = 0;
		data->flag_s = 0;
		i = 0;
		while (lexer_clone->value[i])
		{
			if (lexer_clone->value[i] == '"' && data->flag_s == 0)
				ft_change_flag(data->flag_d);
			if (lexer_clone->value[i] == '\'' && data->flag_d == 0)
				ft_change_flag(data->flag_s);
			if (data->flag_s == 0 && lexer_clone->value[i] == '$'
				&& lexer_clone->value[i + 1] == '?')
				lexer_clone->value = ft_change_value(data, lexer_clone->value);
			i++;
		}
		lexer_clone = lexer_clone->next;
	}
}
