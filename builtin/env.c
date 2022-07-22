#include "../minishell.h"

void	ft_env_built(t_data *data)
{
	t_env	*env_clone;

	env_clone = data->lst_env;
	if (env_clone)
	{
		while (env_clone)
		{
			if (env_clone->value && strlen(env_clone->value))
				printf("%s=%s\n", env_clone->name, env_clone->value);
			env_clone = env_clone->next;
		}
	}
	else
		HERE
}
