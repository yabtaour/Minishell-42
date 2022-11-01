/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 10:55:33 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/10/07 14:27:35 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_delim_idx(t_data *data, t_cmd *cmd)
{
	if (cmd->prev)
		data->general.index += cmd->prev->her_doc_num;
	return (data->general.index);
}

void	print_her_in(t_cmd *cmd, char *here_buff)
{
	ft_putstr_fd(here_buff, cmd->her_in);
	ft_putstr_fd("\n", cmd->her_in);
	free(here_buff);
}
