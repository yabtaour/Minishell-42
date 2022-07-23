#include "../minishell.h"

char	*ft_get_env(t_data *data, char *name)
{
	t_env	*env_clone;

	env_clone = data->lst_env;
	if (!name)
		return (NULL);
	while (env_clone)
	{
		if (strncmp(name, env_clone->name, strlen(name)) == 0)
			return (env_clone->value);
		env_clone = env_clone->next;
	}
	return (NULL);
}
