#include "../minishell.h"

void	ft_env(t_data *data)
{
	ft_create_env_list(&data->lst_env, data->env);
}
