#include "../minishell.h"

// t_cmd	*ft_new_cmd_node(char *cmd, char *option, char *argument)
// {
// 	t_cmd	*node;
// 	int		i;
// 	int		count = 0;
// 	int		options_num = 0;
// 	int		arguments_num = 0;

// 	node = NULL;
// 	if (!cmd && !option && !argument)
// 		return (NULL);

// 	node = malloc(sizeof(t_cmd));
// 	node->option = NULL;
// 	node->argument = NULL;
// 	if (!node)
// 		return (NULL);
// 	if (option)
// 	{
// 		while (option[count])
// 		{
// 			if ((option[count] == ' ' && option[count + 1] == '-') || (option[count] == 0 && option[count] == '-'))
// 				options_num++;
// 			count++;
// 		}
// 		node->option = malloc(sizeof(char *) * options_num);
// 		node->option = ft_split(option, ' ');
// 	}
// 	if (argument)
// 	{
// 		count = 0;
// 		while (argument[count])
// 		{
// 			if (argument[count] == ' ' && argument[count + 1] != '-')
// 				arguments_num++;
// 			count++;
// 		}
// 		node->argument = malloc(sizeof(char *) * arguments_num);
// 		node->argument = ft_split(argument, ' ');
// 	}
// 	if (cmd)
// 	{
// 		i = strlen(cmd);
// 		node->cmd = malloc(i + 1);
// 		i = -1;
// 		while (cmd[++i])
// 			node->cmd[i] = cmd[i];
// 		node->cmd[i] = '\0';
// 	}
// 	node->next = NULL;
// 	node->prev = NULL;
// 	return (node);
// }

// int	ft_check_command(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '-' || str[i] == '>' || str[i] == '<')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// t_cmd	*ft_add_cmd_back(t_cmd *lst_cmd, char *command)
// {
// 	t_cmd	*node;
// 	t_cmd	*cmd_clone;
// 	char	**all_cmd;
// 	char	*appah = NULL;
// 	char	*cmd = NULL;
// 	char	*options = NULL;
// 	char	*arguments = NULL;
// 	int		i = 0;


// 	if (!command)
// 		return (NULL);
// 	all_cmd = ft_split(command, ' ');
// 	while (all_cmd[i])
// 	{
// 		if (ft_check_command(all_cmd[i]))
// 			cmd = ft_strjoin(cmd, all_cmd[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (all_cmd[i])
// 	{
// 		if (all_cmd[i][0] == '-')
// 			options = ft_join_args(options, all_cmd[i]);
// 		else if (!ft_check_command(all_cmd[i]))
// 			arguments = ft_join_args(arguments, all_cmd[i]);
// 		i++;
// 	}
// 	printf("command %s\n", cmd);
// 	printf("opt %s\n", options);
// 	printf("args %s\n", arguments);
// 	// cmd = ft_strjoin(cmd, options);
// 	// cmd = ft_strjoin(cmd, arguments);
// 	printf("the final command is %s\n", cmd);
// 	// node = ft_new_cmd_node(cmd, options, arguments);
// 	// if (!lst_cmd)
// 	// 	return (node);
// 	// cmd_clone = lst_cmd;
// 	// while (cmd_clone->next)
// 	// 	cmd_clone = cmd_clone->next;
// 	// node->prev = cmd_clone;
// 	// cmd_clone->next = node;
// 	return (lst_cmd);
// }

// void	ft_add_command_pipe(t_data *data)
// {
// 	t_lexer	*lexer_clone;
// 	t_cmd	*cmd_clone;
// 	char	*command;

// 	lexer_clone = data->lst_lexer;
// 	while (lexer_clone)
// 	{
// 		command = NULL;
// 		while (lexer_clone->type != PIPE && lexer_clone->next)
// 		{
// 			command = ft_strjoin(command, lexer_clone->value);
// 			lexer_clone = lexer_clone->next;
// 		}
// 		if (!lexer_clone->next)
// 			command = ft_strjoin(command, lexer_clone->value);
// 		data->lst_cmd = ft_add_cmd_back(data->lst_cmd, command);
// 		lexer_clone = lexer_clone->next;
// 	}
// }