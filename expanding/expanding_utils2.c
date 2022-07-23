#include "../minishell.h"

int	ft_check_still_dollar(t_data *data)
{
	t_lexer	*lexer_clone;
	int		i;

	lexer_clone = data->lst_lexer;
	while (lexer_clone)
	{
		data->flag_d = 0;
		data->flag_s = 0;
		i = -1;
		while (lexer_clone->value[++i])
		{
			if (lexer_clone->value[i] == '"' && data->flag_s == 0)
				data->flag_d = ft_change_flag(data->flag_d);
			if (lexer_clone->value[i] == '\'' && data->flag_d == 0)
				data->flag_s = ft_change_flag(data->flag_s);
			if (data->flag_s == 0 && lexer_clone->value[i] == '$'
				&& lexer_clone->value[i + 1]
				&& lexer_clone->value[i + 1] != '"'
				&& lexer_clone->value[i + 1] != '?')
				return (1);
		}
		lexer_clone = lexer_clone->next;
	}
	return (0);
}

char	*ft_fix_norme(char *n_v, char *value, int i)
{
	return (ft_strjoin(n_v, ft_substr(value, i, ft_strlen(value))));
}

char	*ft_change_nd_free(char *value, char *var, char *n_v)
{
	free(value);
	value = ft_substr(n_v, 0, ft_strlen(n_v));
	free(var);
	free(n_v);
	return (value);
}
