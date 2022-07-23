#include "../minishell.h"

void	ft_create_env_list(t_env **envi, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		*envi = ft_add_to_env_back(*envi, env[i++]);
}

void	ft_env(t_data *data)
{
	ft_create_env_list(&data->lst_env, data->env);
}
