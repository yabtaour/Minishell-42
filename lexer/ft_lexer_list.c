/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:16:46 by yabtaour          #+#    #+#             */
/*   Updated: 2022/09/15 18:08:50 by ssabbaji         ###   ########.fr       */
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
		exit (1);
	node->val = malloc(i + 1);
	if (!node->val)
		exit (1);
	i = -1;
	while (str[++i])
		node->val[i] = str[i];
	node->val[i] = '\0';
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
		exit (1);
	if (lexer == NULL)
		return (node);
	lexer_clone = lexer;
	while (lexer_clone->next != NULL)
		lexer_clone = lexer_clone->next;
	lexer_clone->next = node;
	node->prev = lexer_clone;
	return (lexer);
}
