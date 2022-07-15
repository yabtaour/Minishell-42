#include "../minishell.h"

// name cant have - or number flwl or + matab3ahach =
// if matalan x+=2 and x makaynach f env ghatwli x=2

// void	ft_sort_env(t_data *data)
// {
// 	t_env	*env_clone;
// 	t_env	*env_clone;
// }

int	ft_name_size(char *name)
{
	int	i = 0;

	if (!name)
		return (0);
	while (name[i] && name[i] != '=')
		i++;
	return (i);
}

int	ft_value_size(char *value)
{
	int	i = 0;
	int	j = 0;

	if (!value)
		return (0);
	while (value[i] && value[i] != '=')
		i++;
	if (!value[i])
		return (0);
	while (value[++i])
		j++;
	return (j);
}

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

int	ft_change_env_value(t_data *data, char *name, char *value, int	value_size)
{
	t_env	*env_clone;
	int		i = 0;

	env_clone = data->lst_env;
	if (!value)
		return (1);
	while (env_clone)
	{
		if (strcmp(name, env_clone->name) == 0)
		{
			free(env_clone->value);
			env_clone->value = malloc (value_size + 1);
			while (value[i])
			{
				env_clone->value[i] = value[i];
				i++;
			}
			env_clone->value[i] = '\0';
			break;
		}
		env_clone = env_clone->next;
	}
	return (0);
}

t_env	*ft_new_node(char *name, char *value)
{
	t_env	*node;
	int		i = -1;

	if (!name || !value)
		return (NULL);
	node = malloc (sizeof(t_env));
	if (!node)
		return (NULL);
	node->name = malloc (strlen(name) + 1);
	node->value = malloc (strlen(value) + 1);
	if (!node->name || !node->value)
		return (NULL);
	while (name[++i])
		node->name[i] = name[i];
	node->name[i] = '\0';
	i = -1;
	while (value[++i])
		node->value[i] = value[i];
	node->value[i] = '\0';
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	ft_add_new_env(t_data *data, char *name, char *value)
{
	t_env	*env_clone;
	t_env	*new_node;

	env_clone = data->lst_env;
	while (env_clone->next)
		env_clone = env_clone->next;
	new_node = ft_new_node(name, value);
	if (new_node)
	{
		env_clone->next = new_node;
		new_node->prev = env_clone;
	}
}

void	ft_sort_env(t_data *data)
{
	t_env	*env_clone;
	char	*name_tmp = NULL;
	char	*value_tmp = NULL;
	t_env	*env_clone2;
	t_env	*env_tmp;

	env_clone = data->lst_env;
	printf("%s\n", data->first_export);
	while (env_clone && (!data->first_export || strcmp(env_clone->name, data->first_export)))
	{
		env_clone2 = env_clone->next;
		if (env_clone2)
		{
			while (env_clone2 && (!data->first_export || strcmp(env_clone2->name, data->first_export)))
			{
				if (strcmp(env_clone->name, env_clone2->name) > 0)
				{
					name_tmp = malloc (strlen(env_clone->name) + 1);
					value_tmp = malloc (strlen(env_clone->value) + 1);
					strcpy(name_tmp, env_clone->name);
					strcpy(value_tmp, env_clone->value);
					free(env_clone->name);
					free(env_clone->value);
					env_clone->name = malloc(strlen(env_clone2->name) + 1);
					env_clone->value = malloc(strlen(env_clone2->value) + 1);
					strcpy(env_clone->name, env_clone2->name);
					strcpy(env_clone->value, env_clone2->value);
					free(env_clone2->name);
					free(env_clone2->value);
					env_clone2->name = malloc(strlen(name_tmp) + 1);
					env_clone2->value = malloc(strlen(value_tmp) + 1);
					env_clone2->name = name_tmp;
					env_clone2->value = value_tmp;
				}
				env_clone2 = env_clone2->next;
			}
		}
		env_clone = env_clone->next;
	}
	while (env_clone)
	{
		env_clone2 = env_clone->next;
		while (env_clone2)
		{
			if (strcmp(env_clone->name, env_clone2->name) > 0)
			{
				name_tmp = malloc (strlen(env_clone->name) + 1);
				value_tmp = malloc (strlen(env_clone->value) + 1);
				strcpy(name_tmp, env_clone->name);
				strcpy(value_tmp, env_clone->value);
				free(env_clone->name);
				free(env_clone->value);
				env_clone->name = malloc(strlen(env_clone2->name) + 1);
				env_clone->value = malloc(strlen(env_clone2->value) + 1);
				strcpy(env_clone->name, env_clone2->name);
				strcpy(env_clone->value, env_clone2->value);
				free(env_clone2->name);
				free(env_clone2->value);
				env_clone2->name = malloc(strlen(name_tmp) + 1);
				env_clone2->value = malloc(strlen(value_tmp) + 1);
				env_clone2->name = name_tmp;
				env_clone2->value = value_tmp;
			}
			env_clone2 = env_clone2->next;			
		}
		env_clone = env_clone->next;
	}
}

int	export(t_data *data, t_cmd *lst_cmd, int fd)
{
	char	*name = NULL;
	char	*value = NULL;
	int		i = 0;
	int		j = 0;

	if (lst_cmd && !lst_cmd->cmd[1])
	{
		ft_sort_env(data);
		ft_print_env(data->lst_env, 1, fd);
	}
	if (lst_cmd && lst_cmd->cmd[1])
	{
		if (ft_name_size(lst_cmd->cmd[1]))
		{
			name = malloc(ft_name_size(lst_cmd->cmd[1]) + 1);
			if (!name)
				return (1);
			while (lst_cmd->cmd[1][i] && lst_cmd->cmd[1][i] != '=')
			{
				name[i] = lst_cmd->cmd[1][i];
				i++;
			}
			name[i] = '\0';
		}
		if (lst_cmd->cmd[1][i])
		{
			i++;
			if (ft_value_size(lst_cmd->cmd[1]))
			{
				value = malloc(ft_value_size(lst_cmd->cmd[1]) + 1);
				if (!value)
					return (1);
				while (lst_cmd->cmd[1][i])
				{
					value[j] = lst_cmd->cmd[1][i];
					i++;
					j++;
				}
				value[j] = '\0';
			}
		}
		if (ft_name_exists(data, name))
			ft_change_env_value(data, name, value, ft_value_size(lst_cmd->cmd[1]));
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