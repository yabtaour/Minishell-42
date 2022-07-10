#include "../minishell.h"

char	*ft_change_lexer(char *env_name, char *lexer_value)
{
	int	i;

	i = 0;
	free(lexer_value);
	lexer_value = malloc(strlen(env_name) + 1);
	while (env_name[i])
	{
		lexer_value[i] = env_name[i];
		i++;
	}
	lexer_value[i] = '\0';
	return (lexer_value);
}

char	*ft_change_var(char *var, t_data *data)
{
	char	*after_dollar;
	char	*result = NULL;
	t_env	*env_clone;

	if (!var)
		return (NULL);
	env_clone = data->lst_env;
	after_dollar = ft_substr(var, 1, strlen(var));
	free(var);
	while (env_clone)
	{
		if (strcmp(after_dollar, env_clone->name) == 0)
		{
			result = malloc(strlen(env_clone->value) + 1);
			result = ft_substr(env_clone->value, 0, strlen(env_clone->value));
			free(after_dollar);
		}
		env_clone = env_clone->next;
	}
	return (result);
}

int		ft_check_still_dollar(t_data *data)
{
	t_lexer	*lexer_clone;
	int		i;

	lexer_clone = data->lst_lexer;
	while (lexer_clone)
	{
		if (lexer_clone->type == DOUBLE_QUOTES)
		{
			i = 0;
			while (lexer_clone->value[i])
			{
				if (lexer_clone->value[i] == '$')
					return (1);
				i++;
			}
		}
		lexer_clone = lexer_clone->next;
	}
	return (0);
}

void	ft_check_var_quotes(t_data *data)
{
	t_lexer	*lexer_clone;
	char	*before_var = NULL;
	char	*var = NULL;
	char	*after_var = NULL;
	int		i = 0;
	int		origin;
	int		j = 0;

	lexer_clone = data->lst_lexer;
	while (ft_check_still_dollar(data))
	{
		lexer_clone = data->lst_lexer;
	while (lexer_clone)
	{
		i = 0;
		if (lexer_clone->type == DOUBLE_QUOTES)
		{
			i = 0;
			while (lexer_clone->value[i] != '$' && lexer_clone->value[i] != '\0')
				i++;
			if (lexer_clone->value[i] == '$')
			{
				origin = i;
				j = 0;
				before_var = malloc(i + 1);
				before_var = ft_substr(lexer_clone->value, 0, i);
				i++;
				while (lexer_clone->value[i] != ' ' && lexer_clone->value[i] != '\0' && lexer_clone->value[i] != '"' && lexer_clone->value[i] != '$' && lexer_clone->value[i] != '\\')
				{
					i++;
					j++;
				}
				var = malloc(j + 2);
				var = ft_substr(lexer_clone->value, origin, j + 1);
				var = ft_change_var(var, data);
				if (var)
					before_var = ft_strjoin(before_var, var);
				if (lexer_clone->value[i] == '"')
					before_var = ft_strjoin(before_var, "\"");
				origin = i;
				if (lexer_clone->value[i] == ' ' || lexer_clone->value[i] == '$' || lexer_clone->value[i] == '\\')
				{
					j = 0;
					while (lexer_clone->value[i] != '\0')
					{
						j++;
						i++;
					}
					after_var = malloc (j + 1);
					after_var = ft_substr(lexer_clone->value, origin, j);
					before_var = ft_strjoin(before_var, after_var);
				}
				lexer_clone->value = before_var;
			}
		}
		lexer_clone = lexer_clone->next;
	}
	}
}

int		ft_len_var(char *lexer)
{
	int	i = 1;

	if (lexer)
	{
		while (lexer[i])
		{
			if (lexer[i] == '$' || lexer[i] == '"' || lexer[i] == ' ' || lexer[i] == '\\')
				break ;
			i++;
		}
	}
	return (i);
}

void	ft_delete_node(t_data *data)
{
	t_lexer	*lexer_clone;
	int		i;

	i = 0;
	lexer_clone = data->lst_lexer;
	while (lexer_clone)
	{
		i = 0;
		if (lexer_clone->type == DOLLAR)
		{
			while (lexer_clone->value[i])
			{
				if (lexer_clone->value[i] == '$')
				{
					if (lexer_clone->next)
						lexer_clone->next->prev = lexer_clone->prev;
					lexer_clone->prev->next = lexer_clone->next;
					free(lexer_clone);
					break;
				}
				i++;
			}
		}
		lexer_clone = lexer_clone->next;
	}
}

void	ft_expanding(t_data *data)
{
	t_lexer	*lexer_clone;
	t_env	*env_clone;
	char	*value;
	int		len;

	lexer_clone = data->lst_lexer;
	while (lexer_clone)
	{
		if (lexer_clone->type == DOLLAR)
		{
			len = ft_len_var(lexer_clone->value);
			value = ft_substr(lexer_clone->value, 1, len);
			printf("%s\n", value);
			env_clone = data->lst_env;
			while (env_clone)
			{
				if (strcmp(env_clone->name, value) == 0)
					lexer_clone->value = ft_change_lexer(env_clone->value, value);
				env_clone = env_clone->next;
			}
		}
		lexer_clone = lexer_clone->next;
	}
	ft_check_var_quotes(data);
	ft_delete_node(data);
}