#include "../minishell.h"

void	ft_change_env(t_data *data, char *name, char *value)
{
	t_env	*env_clone;
	int		i;

	i = 0;
	env_clone = data->lst_env;
	while (env_clone)
	{
		if (strncmp(name, env_clone->name, strlen(name)) == 0)
		{
			free(env_clone->value);
			env_clone->value = malloc (strlen(value) + 1);
			if (!env_clone)
				break;
			while (value[i])
			{
				env_clone->value[i] = value[i];
				i++;
			}
			env_clone->value[i] = '\0';
			break;
		}
		env_clone = env_clone->next;
	}
}


// the cd cmnds should be in the parent process 
int cd(t_data *data, t_cmd *lst_cmd)
{
	int direrror;
	char *current_wd;
	char *new_wd;

	current_wd = NULL;
	new_wd = NULL;
	if (lst_cmd)
	{
		current_wd = getcwd(current_wd, 0);
		if (!current_wd)
		{
			printf("cd: getcwd: cannot access parent directories: No such file or directory\n");
		}
		else
		{
			if (!lst_cmd->cmd[1])
			{
				new_wd = ft_get_env(data ,"HOME");
			}
			else if (strncmp(lst_cmd->cmd[1], "-", 1) == 0)
			{
				new_wd = ft_get_env(data, "OLDPWD");
			}
			else
			{
				new_wd = lst_cmd->cmd[1];
			}
			direrror = chdir(new_wd);
			if (direrror != 0)
				return (1);
			else
			{
				ft_change_env(data, "OLDPWD", current_wd);
				ft_change_env(data, "PWD", new_wd);
			}
			free(current_wd);
		}
	}
	return (0);
}