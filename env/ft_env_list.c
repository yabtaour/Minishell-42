#include "../minishell.h"

t_env	*ft_new_env_node(char *value)
{
	t_env	*node;
	int		i;

	i = 0;
	node = NULL;
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	while (value[i] != '=')
		i++;
	node->name = ft_substr(value, 0, i);
	node->value = ft_substr(value, i + 1, ft_strlen(value) - i);
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_env	*ft_add_to_env_back(t_env *envi, char *value)
{
	t_env	*node;
	t_env	*envi_clone;

	if (!value)
		return (NULL);
	node = ft_new_env_node(value);
	if (envi == NULL)
		return (node);
	envi_clone = envi;
	while (envi_clone->next != NULL)
		envi_clone = envi_clone->next;
	envi_clone->next = node;
	node->prev = envi_clone;
	return (envi);
}
