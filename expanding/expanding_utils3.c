/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 11:30:58 by ssabbaji          #+#    #+#             */
/*   Updated: 2022/10/02 11:31:00 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_var_isnt(t_data *data, char *lexer, char *n_v)
{
	char	*temp;

	temp = ft_delete_var(data, lexer);
	n_v = ft_strjoin(n_v, temp);
	free(temp);
	return (n_v);
}
