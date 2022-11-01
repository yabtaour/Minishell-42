/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabtaour <yabtaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:16:49 by yabtaour          #+#    #+#             */
/*   Updated: 2022/07/26 18:16:50 by yabtaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_parenth(char c)
{
	if (c == '{' || c == '}'
		|| c == '(' || c == ')')
		return (1);
	return (0);
}

int	ft_is_redirection(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	ft_is_word(char c)
{
	if (c != '|' && c != '&' && !ft_is_redirection(c)
		&& !ft_isspace(c) && c != ';' && !ft_is_parenth(c))
		return (1);
	return (0);
}
