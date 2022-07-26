#include "../../minishell.h"

t_env	*ft_new_node(char *name, char *value)
{
	t_env	*node;

	node = malloc (sizeof(t_env));
	if (!node)
		return (NULL);
	node->name = malloc (ft_strlen(name) + 1);
	node->value = malloc (ft_strlen(value) + 1);
	if (!node->name || !node->value)
		return (NULL);
	node->name = ft_substr(name, 0, ft_strlen(name));
	if (value && ft_strlen(value))
		node->value = ft_substr(value, 0, ft_strlen(value));
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
