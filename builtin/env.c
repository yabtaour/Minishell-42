#include "../minishell.h"

int	ft_env_built(t_data *data, int fd)
{
	t_env	*env_clone;

	env_clone = data->lst_env;
	if (env_clone)
	{
		HERE
		while (env_clone)
		{
			if (env_clone->value && ft_strlen(env_clone->value))
			{
				ft_putstr_fd(env_clone->name, fd);
				ft_putstr_fd("=", fd);
				ft_putstr_fd(env_clone->value, fd);
				ft_putstr_fd("\n", fd);
			}
			env_clone = env_clone->next;
		}
	}
	return (0);
}
