/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabtaour <yabtaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:13:32 by yabtaour          #+#    #+#             */
/*   Updated: 2022/07/26 18:17:42 by yabtaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(char *s, int c)
{
	int				i;
	unsigned char	*str;
	unsigned char	k;

	k = (unsigned char)c;
	str = (unsigned char *)s;
	i = 0;
	while (str[i] != '\0' && str[i] != k)
		i++;
	if (str[i] != k)
		return (NULL);
	else
		return ((char *)str + i);
}
