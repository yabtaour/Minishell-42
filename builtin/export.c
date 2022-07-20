#include "../minishell.h"

// name cant have - or number flwl or + matab3ahach =
// if matalan x+=2 and x makaynach f env ghatwli x=2

// void	ft_sort_env(t_data *data)
// {
// 	t_env	*env_clone;
// 	t_env	*env_clone;
// }



int	ft_change_env_value(t_data *data, char *name, char *value, int	value_size)
{
	t_env	*env_clone;
	int		i;

	env_clone = data->lst_env;
	while (env_clone)
	{
		if (strcmp(name, env_clone->name) == 0)
		{
			free(env_clone->value);
			if (!value || !strlen(value))
			{
				env_clone->value = malloc (1);
				env_clone->value[0] = '\0';
			}
			else
			{
				i = -1;
				env_clone->value = malloc (strlen(value) + 1);
				while (value[++i])
					env_clone->value[i] = value[i];
				env_clone->value[i] = '\0';
			}
		}
		env_clone = env_clone->next;
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i = 0;

	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

t_env	*ft_new_node(char *name, char *value)
{
	t_env	*node;
	int		i = -1;

	node = malloc (sizeof(t_env));
	if (!node)
		return (NULL);
	node->name = malloc (strlen(name) + 1);
	node->value = malloc (ft_strlen(value) + 1);
	if (!node->name || !node->value)
		return (NULL);
	node->name = ft_substr(name, 0, strlen(name));
	if (value && strlen(value))
		node->value = ft_substr(value, 0, strlen(value));
	else
		node->value[0] = '\0';
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





