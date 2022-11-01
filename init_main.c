/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 11:28:02 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/10/06 16:36:34 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	init_sig(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}

void	init_main(t_data *data)
{
	g_vars.g_heredoc = 1;
	init_sig();
	ft_initialize2(data);
	g_vars.g_where_ami = 1;
}

void	ft_initialize2(t_data *data)
{
	g_vars.g_where_ami = 1;
	data->lst_cmd = NULL;
	data->lst_lexer = NULL;
	data->her_doc = 0;
	data->general.index = 0;
	g_vars.g_exit_stat = 0;
}
