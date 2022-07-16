#include "../minishell.h"

int unset(t_data *data, t_cmd *lst_cmd)
{
    int idx;
	t_env	*env_clone;
    t_env   *tmp;

    printf("name : %s\n", lst_cmd->cmd[1]);
    // ft_print_env(data->lst_env, 0, 1);
	idx = 1;
    env_clone = data->lst_env;
	if (!lst_cmd->cmd[1])
		return (1);
	while (env_clone)
	{
        // if (!env_clone->next)
        //     return (1);
		if (strcmp(lst_cmd->cmd[idx], env_clone->name) == 0)
        {
            // printf("name : %s\n", lst_cmd->cmd[idx]);
            if (env_clone->next)
                env_clone->next->prev = env_clone->prev;
            if (env_clone->prev)
                env_clone->prev->next = env_clone->next;
            free(env_clone);
            idx++;
            if (!lst_cmd->cmd[idx])
                return (0);
            // ft_print_env(data->lst_env, 0, 1);
        }
        if (env_clone)
           env_clone = env_clone->next;
	}

    // ft_print_env(data->lst_env, 0, 1);
	return (0);
}