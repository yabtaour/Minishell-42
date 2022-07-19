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
		if (lexer_clone->type == WORD)
		{
			i = 0;
			while (lexer_clone->value[i])
			{
				if (lexer_clone->value[i] == '"' && data->flag_s == 0)
					data->flag_d = ft_change_flag(data->flag_d);
				if (lexer_clone->value[i] == '\'' && data->flag_d == 0)
					data->flag_s = ft_change_flag(data->flag_s);
				if (data->flag_s == 0 && lexer_clone->value[i] == '$' && lexer_clone->value[i + 1]
					&& lexer_clone->value[i + 1] != '"' && data->flag_s == 0)
					return (1);
				i++;
			}
		}
		lexer_clone = lexer_clone->next;
	}
	return (0);
}

void	ft_expanding(t_data *data)
{
	t_lexer	*lexer_clone;
	t_env	*env_clone;
	char	*new_var;
	char	*var;
	int		i = 0;
	char	*before_var;
	int		flag_d = 0;
	int		flag_s = 0;

	lexer_clone = data->lst_lexer;
	while (ft_check_still_dollar(data))
	{
		lexer_clone = data->lst_lexer;
		while (lexer_clone)
		{
			flag_d = 0;
			flag_s = 0;
			i = 0;
			var = NULL;
			new_var = NULL;					
			if (lexer_clone->type == WORD)
			{
				i = 0;
				new_var = ft_strjoin(new_var, ft_substr(lexer_clone->value, 0, ft_len_before(lexer_clone->value)));
				while (flag_s == 1 || (lexer_clone->value[i] && lexer_clone->value[i] != '$'))
				{
					if (lexer_clone->value[i] == '"' && flag_s == 0)
						flag_d = ft_change_flag(flag_d);
					if (lexer_clone->value[i] == '\'' && flag_d == 0)
						flag_s = ft_change_flag(flag_s);
					i++;
				}
				if (lexer_clone->value[i] && lexer_clone->value[i + 1])
					var = ft_substr(lexer_clone->value, i + 1, ft_len_var(lexer_clone->value));
				else
				{
					if (var)
					{
						free (lexer_clone->value);
						lexer_clone->value = ft_substr(new_var, 0, strlen(new_var));
					}
				}
				if (var)
				{
					if (ft_check_var_env(data, var))
					{
						new_var = ft_strjoin(new_var, ft_get_value(data, var));
						i++;
						while (lexer_clone->value[i] && lexer_clone->value[i] != ' ' && lexer_clone->value[i] != '$'
							&& lexer_clone->value[i] != '\\' && lexer_clone->value[i] != '"' && lexer_clone->value[i] != '\'' && lexer_clone->value[i] != '=')
							i++;
					if (lexer_clone->value[i])
						new_var = ft_strjoin(new_var, ft_substr(lexer_clone->value, i, ft_len_after(lexer_clone->value)));
					}
					else
						new_var = ft_strjoin(new_var, ft_delete_var(data, lexer_clone->value));
					free (lexer_clone->value);
					lexer_clone->value = ft_substr(new_var, 0, strlen(new_var));				
				}
				free(new_var);
				free(var);
			}
			lexer_clone = lexer_clone->next;
		}
	}
}