/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabtaour <yabtaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:17:19 by yabtaour          #+#    #+#             */
/*   Updated: 2022/07/27 16:40:21 by yabtaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check_pipe(t_data *data)
{
	t_lexer	*lexer_clone;

	lexer_clone = data->lst_lexer;
	while (lexer_clone)
	{
		if (lexer_clone->type == PIPE)
			return (1);
		lexer_clone = lexer_clone->next;
	}
	return (0);
}

int	ft_check_still_redirection(t_data *data)
{
	t_lexer	*lexer_clone;

	lexer_clone = data->lst_lexer;
	while (lexer_clone && lexer_clone->type != PIPE)
	{
		if (lexer_clone->type == REDIRECTION
			&& ft_strcmp(lexer_clone->value, "<<"))
			return (1);
		lexer_clone = lexer_clone->next;
	}
	return (0);
}

void	ft_add_normal_command(t_data *data)
{
	int		*red;
	int		red_num;
	t_lexer	*lexer_clone;
	int		*fd;
	int		i;

	i = 0;
	red_num = ft_red_num(data);
	red = ft_fill_red(data, red_num);
	fd = malloc (sizeof(int) * red_num);
	if (!fd)
		exit (1);
	lexer_clone = data->lst_lexer;
	while (lexer_clone && lexer_clone->type != PIPE)
	{
		if (lexer_clone->type == REDIRECTION
			&& ft_strcmp(lexer_clone->value, "<<"))
		{
			lexer_clone = lexer_clone->next;
			fd[i] = ft_fill_fd(data, lexer_clone->value, red[i]);
			i++;
		}
		lexer_clone = lexer_clone->next;
	}
	data->lst_cmd = ft_add_back_cmd(data, fd, red, red_num);
}

int	ft_check_still_pipe(t_data *data)
{
	t_lexer	*lexer_clone;

	lexer_clone = data->lst_lexer;
	while (lexer_clone)
	{
		if ((lexer_clone) || lexer_clone->type == PIPE)
			return (1);
		lexer_clone = lexer_clone->next;
	}
	return (0);
}

void	ft_parsing(t_data *data)
{
	t_lexer	*lexer_clone;

	lexer_clone = data->lst_lexer;
	ft_change_exit_status(data);
	ft_handle_herdoc(data, lexer_clone);
	ft_add_command_pipe(data);
	ft_delete_quotes(data);
}
