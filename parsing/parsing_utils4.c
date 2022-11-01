/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:17:15 by yabtaour          #+#    #+#             */
/*   Updated: 2022/08/08 16:59:06 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	word_count(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			if ((s[i - 1] == c || i == 0))
				count++;
			i++;
		}
	}
	return (count);
}

char	**ft_free_tab(char	**str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
	return (str);
}

static char	**ft_allocation(char const *s, char c)
{
	char	**ptr;

	if (s == NULL)
		return (NULL);
	ptr = ft_calloc((word_count(s, c) + 1), sizeof(char *));
	return (ptr);
}

char	**ft_split(char *s, char c)
{
	char	**ptr;
	int		j;
	int		i;

	ptr = ft_allocation(s, c);
	if (!ptr)
		return (ptr);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		j = 0;
		while (s[j] != '\0' && s[j] != c)
			j++;
		if (j != 0)
		{
			ptr[i] = ft_substr(s, 0, j);
			if (ptr[i] == NULL)
				return (ft_free_tab(ptr, i));
			i++;
		}
		s = s + j;
	}
	return (ptr);
}
