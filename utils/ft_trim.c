/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabtaour <yabtaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:49:39 by yabtaour          #+#    #+#             */
/*   Updated: 2022/07/26 19:41:22 by yabtaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strtrim(char *s1, char *set)
{
	size_t	start;
	size_t	last;
	char	*ptr;

	ptr = NULL;
	if (s1 != NULL && set != NULL)
	{
		start = 0;
		last = ft_strlen(s1);
		while (s1[start] != '\0' && ft_strchr(set, s1[start]))
			start++;
		while (ft_strchr(set, s1[last - 1]) && last > start)
			last--;
		ptr = (char *)malloc(sizeof(char) * (last - start + 1));
		if (!ptr)
			exit (1);
		if (ptr)
			strlcpy(ptr, s1 + start, last - start + 1);
	}
	return (ptr);
}