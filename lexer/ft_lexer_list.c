/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabtaour <yabtaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:16:46 by yabtaour          #+#    #+#             */
/*   Updated: 2022/07/26 18:16:47 by yabtaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*ft_new_lexer_node(char *str, int type)
{
	t_lexer	*node;
	int		i;

	node = NULL;
	if (!str)
		return (NULL);
	i = ft_strlen(str);
	node = malloc(sizeof(t_lexer));
	if (!node)
		return (NULL);
	node->value = malloc(i + 1);
	i = -1;
	while (str[++i])
		node->value[i] = str[i];
	node->value[i] = '\0';
	node->type = type;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_lexer	*ft_add_lexer_back(t_lexer *lexer, char *str, int type)
{
	t_lexer	*node;
	t_lexer	*lexer_clone;

	if (!str)
		return (NULL);
	node = ft_new_lexer_node(str, type);
	if (!node)
		return (NULL);
	if (lexer == NULL)
		return (node);
	lexer_clone = lexer;
	while (lexer_clone->next != NULL)
		lexer_clone = lexer_clone->next;
	lexer_clone->next = node;
	node->prev = lexer_clone;
	return (lexer);
}
