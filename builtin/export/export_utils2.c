#include "../../minishell.h"

t_env	*ft_new_node(char *name, char *value)
{
	t_env	*node;

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

void	ft_swap_name(t_env *clone1, t_env *clone2)
{
	char	*name_tmp;
	int		len;

	len = ft_strlen(clone1->name);
	name_tmp = ft_substr(clone1->name, 0, len);
	free(clone1->name);
	len = ft_strlen(clone2->name);
	clone1->name = ft_substr(clone2->name, 0, len);
	free(clone2->name);
	len = ft_strlen(name_tmp);
	clone2->name = ft_substr(name_tmp, 0, len);
	free(name_tmp);	
}

void	ft_swap_value(t_env *clone1, t_env *clone2)
{
	char	*value_tmp;
	int		len;

	len = ft_strlen(clone1->value);
	value_tmp = ft_substr(clone1->value, 0, len);
	free(clone1->value);
	len = ft_strlen(clone2->value);
	clone1->value = ft_substr(clone2->value, 0, len);
	free(clone2->value);
	len = ft_strlen(value_tmp);
	clone2->value = ft_substr(value_tmp, 0, len);
	free(value_tmp);	
}

void	ft_sort_original(t_data *data)
{
	t_env	*env_clone;
	t_env	*env_clone2;
	t_cmd	*env_temp;
	char	*name_tmp;
	char	*value_temp;

	env_clone = data->lst_env;
	while (env_clone && (!data->first_export
			|| strcmp(env_clone->name, data->first_export)))
	{
		env_clone2 = env_clone->next;
		while (env_clone2 && (!data->first_export
				|| strcmp(env_clone2->name, data->first_export)))
		{
			if (strcmp(env_clone->name, env_clone2->name) > 0)
			{
				ft_swap_name(env_clone, env_clone2);
				ft_swap_value(env_clone, env_clone2);
			}
			env_clone2 = env_clone2->next;
		}
		env_clone = env_clone->next;
	}
}

void	ft_sort_env(t_data *data)
{
	t_env	*env_clone;
	char	*name_tmp;
	char	*value_tmp;
	t_env	*env_clone2;
	t_env	*env_tmp;

	name_tmp = NULL;
	value_tmp = NULL;
	env_clone = data->lst_env;
	ft_sort_original(data);
	ft_sort_exported(data)
}