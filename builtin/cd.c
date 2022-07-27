#include "../minishell.h"

void	ft_change_env(t_data *data, char *name, char *value)
{
	t_env	*env_clone;
	int		i;

	i = 0;
	env_clone = data->lst_env;
	while (env_clone)
	{
		if (ft_strncmp(name, env_clone->name, ft_strlen(name)) == 0)
		{
			free(env_clone->value);
			env_clone->value = malloc (ft_strlen(value) + 1);
			if (!env_clone)
				exit (1);
			while (value[i])
			{
				env_clone->value[i] = value[i];
				i++;
			}
			env_clone->value[i] = '\0';
			break ;
		}
		env_clone = env_clone->next;
	}
}

int	ft_change_dir(t_data *data, t_cmd *lst_cmd, char *current, char *new)
{
	char	*upd_wd;
	int		direrror;

	upd_wd = NULL;
	if (!lst_cmd->cmd[1])
		new = ft_get_env(data, "HOME");
	else if (ft_strcmp(lst_cmd->cmd[1], "-") == 0)
		new = ft_get_env(data, "OLDPWD");
	else
		new = lst_cmd->cmd[1];
	direrror = chdir(new);
	if (direrror != 0)
		return (1);
	else
	{
		upd_wd = getcwd(upd_wd, 0);
		ft_change_env(data, "OLDPWD", current);
		ft_change_env(data, "PWD", upd_wd);
	}
	free(current);
	return (0);
}

int	ft_error(t_data *data, char *new_wd, char *upd_wd)
{
	int	direrror;

	direrror = 0;
	printf("cd: cannot access parent directories: No such file or directory\n");
	new_wd = ft_get_env(data, "HOME");
	direrror = chdir(new_wd);
	if (direrror != 0)
		return (1);
	else
	{
		new_wd = getcwd(upd_wd, 0);
		ft_change_env(data, "OLDPWD", new_wd);
		ft_change_env(data, "PWD", new_wd);
	}
	return (0);
}

int	cd(t_data *data, t_cmd *lst_cmd)
{
	int		direrror;
	char	*current_wd;
	char	*new_wd;
	char	*upd_wd;

	current_wd = NULL;
	new_wd = NULL;
	upd_wd = NULL;
	if (lst_cmd)
	{
		current_wd = getcwd(current_wd, 0);
		if (!current_wd)
			ft_error(data, new_wd, upd_wd);
		else
			return (ft_change_dir(data, lst_cmd, current_wd, new_wd));
	}
	return (0);
}
