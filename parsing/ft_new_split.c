/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabtaour <yabtaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:17:06 by yabtaour          #+#    #+#             */
/*   Updated: 2022/07/26 18:17:07 by yabtaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	word_count(char *s, char c)
{
	int	i;
	int	count;
	int	flag_d;
	int	flag_s;

	flag_d = 0;
	flag_s = 0;
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '"' && flag_s == 0)
			flag_d = ft_change_flag(flag_d);
		if (s[i] == '\'' && flag_d == 0)
			flag_s = ft_change_flag(flag_s);
		if (flag_d == 0 && flag_s == 0 && (s[i] != c
				&& (!s[i + 1] || s[i + 1] == c)))
			count++;
		i++;
	}
	return (count);
}

char	**ft_allocation(char *s, char c)
{
	char	**ptr;

	ptr = NULL;
	if (!s)
		return (NULL);
	ptr = ft_calloc((word_count(s, c) + 1), sizeof(char *));
	return (ptr);
}

void	ft_initialize_split(t_split *split)
{
	split->d = 0;
	split->i = 0;
	split->j = 6;
	split->s = 0;
	split->ptr = NULL;
}

void	ft_flag(char c, t_split *split, int flag)
{
	if (c == '"' && split->s == 0)
	{
		split->j++;
		split->d = ft_change_flag(split->d);
		return ;
	}
	if (c == '\'' && split->d == 0)
	{
		split->j++;
		split->s = ft_change_flag(split->s);
		return ;
	}
	if (flag)
		split->j++;
}

char	**ft_new_split(char *s, char c)
{
	t_split	split;

	ft_initialize_split(&split);
	split.ptr = ft_allocation(s, c);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		split.j = 0;
		ft_flag(*s, &split, 0);
		while ((s[split.j] && (split.d == 1 || split.s == 1))
			|| (s[split.j] != '\0' && s[split.j] != c))
			ft_flag(s[split.j], &split, 1);
		if (split.j)
		{
			split.ptr[split.i] = ft_substr(s, 0, split.j);
			if (!split.ptr[split.i])
				return (ft_free_tab(split.ptr, split.i));
			split.i++;
		}	
		s = s + split.j;
	}
	return (split.ptr);
}

// char	**ft_new_split(char *s, char c)
// {
// 	char	**ptr;
// 	int		j;
// 	int		i;
// 	int		flag_d = 0;
// 	int		flag_s = 0;

// 	ptr = ft_allocation(s, c);
// 	i = 0;
// 	while (*s)
// 	{
// 		while (*s && *s == c)
// 			s++;
// 		j = 0;
// 		if (*s == '"' && flag_s == 0)
// 		{
// 			j++;
// 			flag_d = ft_change_flag(flag_d);
// 		}
// 		if (*s == '\'' && flag_d == 0)
// 		{
// 			j++;
// 			flag_s = ft_change_flag(flag_s);
// 		}
// 		while ((s[j] && (flag_d == 1 || flag_s == 1)) 
// || (s[j] != '\0' && s[j] != c))
// 		{
// 			if (s[j] == '"' && flag_s == 0)
// 				flag_d = ft_change_flag(flag_d);
// 			if (s[j] == '\'' && flag_d == 0)
// 				flag_s = ft_change_flag(flag_s);
// 			j++;
// 		}
// 		if (j)
// 		{
// 			ptr[i] = ft_substr(s, 0, j);
// 			i++;
// 		}	
// 		s = s + j;
// 	}
// 	return (ptr);
// }