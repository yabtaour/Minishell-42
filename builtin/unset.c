#include "../minishell.h"

int unset(t_data *data, char *name)
{
	t_env	*env_clone;
    t_env   *tmp;

    ft_print_env(data->lst_env, 0, 1);
	env_clone = data->lst_env;
	if (!name)
		return (1);
	while (env_clone)
	{
        if (!env_clone->next)
            return (1);
		if (strcmp(name, env_clone->name) == 0)
        {
            if (env_clone->next)
                env_clone->next->prev = env_clone->prev;
            if (env_clone->prev)
                env_clone->prev->next = env_clone->next;
            free(env_clone);
            ft_print_env(data->lst_env, 0, 1);
            return (0);
        }
        if (env_clone)
           env_clone = env_clone->next;
	}
    ft_print_env(data->lst_env, 0, 1);
	return (0);
}