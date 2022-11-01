/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:17:10 by yabtaour          #+#    #+#             */
/*   Updated: 2022/10/03 14:24:02 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_get_in(int *fd, int *red, int red_num)
{
	int	fd_in;
	int	i;

	fd_in = 0;
	i = 0;
	while (i < red_num)
	{
		if (red[i] == 3)
			fd_in = fd[i];
		i++;
	}
	return (fd_in);
}

int	ft_get_out(int *fd, int *red, int red_num)
{
	int	fd_out;
	int	i;

	fd_out = 1;
	i = 0;
	while (i < red_num)
	{
		if (red[i] == 1 || red[i] == 2)
			fd_out = fd[i];
		i++;
	}
	return (fd_out);
}

int	*ft_fill_red(t_data *data, int red_num)
{
	t_lexer	*lexer_clone;
	int		*red;
	int		i;

	i = 0;
	red = malloc(sizeof(int) * red_num);
	if (!red)
		exit (1);
	lexer_clone = data->lst_lexer;
	while (lexer_clone && lexer_clone->type != PIPE)
	{
		if (ft_strcmp(lexer_clone->val, ">") == 0)
			red[i++] = 1;
		if (ft_strcmp(lexer_clone->val, ">>") == 0)
			red[i++] = 2;
		if (ft_strcmp(lexer_clone->val, "<") == 0)
			red[i++] = 3;
		lexer_clone = lexer_clone->next;
	}
	return (red);
}

int	ft_fill_fd(t_data *data, char *name, int red)
{
	int	fd;

	(void)data;
	if (red == 1)
		fd = open(name, O_RDWR | O_CREAT | O_TRUNC | O_CLOEXEC, 0664);
	if (red == 2)
		fd = open(name, O_RDWR | O_CREAT | O_APPEND | O_CLOEXEC, 0664);
	if (red == 3)
	{
		fd = open(name, O_RDONLY | O_CLOEXEC, 0777);
		if (fd == -1)
		{
			printf("No such file or directory\n");
			data->rerror_f = 1;
			g_vars.g_exit_stat = 1;
			fd = -69;
		}
	}
	return (fd);
}

int	ft_red_num(t_data *data)
{
	int		red_num;
	t_lexer	*lexer_clone;

	red_num = 0;
	lexer_clone = data->lst_lexer;
	while (lexer_clone && lexer_clone->type != PIPE)
	{		
		if (lexer_clone->type == REDIRECTION
			&& ft_strcmp(lexer_clone->val, "<<"))
			red_num++;
		lexer_clone = lexer_clone->next;
	}
	return (red_num);
}
