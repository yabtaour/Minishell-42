#include "../../minishell.h"

int	ft_name_exists(t_data *data, char *name)
{
	t_env	*env_clone;

	if (!name)
		return (0);
	env_clone = data->lst_env;
	while (env_clone)
	{
		if (strcmp(name, env_clone->name) == 0)
			return (1);
		env_clone = env_clone->next;
	}
	return (0);
}

char	*ft_get_name_exp(char *name)
{
	int		i;
	char	*new_name;

	new_name = NULL;
	i = 0;
	if (!name)
		return (NULL);
	while (name[i] && name[i] != '=')
		i++;
	new_name = ft_substr(name, 0, i);
	return (new_name);
}

char	*ft_get_value_exp(char *value)
{
	int		i;
	int		j;
	int		origin;
	char	*new_value;

	i = 0;
	j = 0;
	new_value = NULL;
	if (!value)
		return (NULL);
	while (value[i] && value[i] != '=')
		i++;
	if (value[i])
	{
		origin = i + 1;
		while (value[++i])
			j++;
		new_value = ft_substr(value, origin, j);
	}
	return (new_value);
}

void	ft_print_export(t_data *data)
{
	t_env	*env_clone;

	env_clone = data->lst_env;
	while (env_clone)
	{
		printf("%s", env_clone->name);
		if (env_clone->value && strlen(env_clone->value))
			printf("=%s", env_clone->value);
		printf("\n");
		env_clone = env_clone->next;
	}
	
}

int	export(t_data *data, t_cmd *lst_cmd, int fd)
{
	char	*name;
	char	*value;

	if (lst_cmd && !lst_cmd->cmd[1])
	{
		ft_sort_env(data);
		ft_print_export(data);
	}
	if (lst_cmd && lst_cmd->cmd[1])
	{
		name = ft_get_name_exp(lst_cmd->cmd[1]);
		if (!name || strlen(name) == 0)
			return (1);
		value = ft_get_value_exp(lst_cmd->cmd[1]);
		if (ft_name_exists(data, name))
			ft_change_env_value(data, name, value, strlen(value));
		else
		{
			ft_add_new_env(data, name, value);
			if (!data->first_export)
			{
				data->first_export = malloc (strlen(name) + 1);
				strcpy(data->first_export, name);
			}
		}
	}
	return (0);
}