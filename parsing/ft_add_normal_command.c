/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_normal_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsaf <rsaf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 10:21:51 by rsaf              #+#    #+#             */
/*   Updated: 2022/07/28 10:24:20 by rsaf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"

// void	ft_add_normal_command(t_data *data, char *new, int i)
// {
// 	int		*red;
// 	int		red_num;
// 	t_lexer	*lexer_clone;
// 	int		*fd;

// 	red_num = ft_red_num(data);
// 	red = ft_fill_red(data, red_num);
// 	fd = malloc (sizeof(int) * red_num);
// 	if (!fd)
// 		exit (1);
// 	lexer_clone = data->lst_lexer;
// 	while (lexer_clone && lexer_clone->type != PIPE)
// 	{
// 		if (lexer_clone->type == REDIRECTION
// 			&& ft_strcmp(lexer_clone->value, "<<"))
// 		{
// 			lexer_clone = lexer_clone->next;
// 			new = ft_new(lexer_clone->value);
// 			fd[i] = ft_fill_fd(data, new, red[i]);
// 			free(new);
// 			i++;
// 		}
// 		lexer_clone = lexer_clone->next;
// 	}
// 	data->lst_cmd = ft_add_back_cmd(data, fd, red, red_num);
// }