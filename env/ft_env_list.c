#include "../minishell.h"

//---------create envirenment node--------//

t_env	*ft_new_env_node(char *value)
{
	t_env	*node;
	int		i = 0;
	int		j = 0;
	char	*name;

	node = NULL;
	if (!value)
		return (NULL);
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	while (value[i] != '=')
		i++;
	node->name = malloc (i + 1);
	i = -1;
	while (value[++i] != '=')
		node->name[i] = value[i];
	node->name[i] = '\0';
	i = strlen(value) - j;
	node->value = malloc(i * sizeof(char));
	i = -1;
	j = 0;
	while (value[j] != '=')
		j++;
	j++;
	while (value[j])
		node->value[++i] = value[j++];
	node->value[++i] = '\0';
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

//--------add node to the back of envirenment list--------//

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

//------create envirenment list--------//

void	ft_create_env_list(t_env **envi, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		*envi = ft_add_to_env_back(*envi, env[i++]);
}
