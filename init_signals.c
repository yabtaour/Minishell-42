/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsaf <rsaf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:23:26 by rsaf              #+#    #+#             */
/*   Updated: 2022/07/26 12:23:27 by rsaf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handler(int sig)
{
    // printf("%d\n", test);
    if (where_ami == 1)
    {
        if (sig == SIGINT)
        {
  		    rl_replace_line("", 0);
		    write(1, "\n", 1);
		    rl_on_new_line();
		    rl_redisplay();
        }
        if (sig == SIGQUIT)
            signal(SIGQUIT, SIG_IGN);
        return;
    }
}