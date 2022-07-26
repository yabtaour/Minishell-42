/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsaf <rsaf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:22:45 by rsaf              #+#    #+#             */
/*   Updated: 2022/07/26 12:22:46 by rsaf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	close_fds(t_cmd *lst_cmd)
{
	t_cmd	*cmd_clone;

	cmd_clone = lst_cmd;
	while (cmd_clone)
	{
		if (cmd_clone->fd_in != 0)
			close(cmd_clone->fd_in);
		if (cmd_clone->fd_out != 1)
			close(cmd_clone->fd_out);
		cmd_clone = cmd_clone->next;
	}
	return (0);
}
