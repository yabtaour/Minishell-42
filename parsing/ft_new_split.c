#include "../minishell.h"

size_t	word_count(char *s, char c)
{
	int	i = 0;
	int	count = 0;
	int	flag_d = 0;
	int	flag_s = 0;

	while (s[i])
	{
		if (s[i] == '"' && flag_s == 0)
			flag_d = ft_change_flag(flag_d);
		if (s[i] == '\'' && flag_d == 0)
			flag_s = ft_change_flag(flag_s);
		if (flag_d == 0 && flag_s == 0 && (s[i] != c && (!s[i + 1] || s[i + 1] == c)))
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
	ptr = calloc((word_count(s, c) + 1), sizeof(char *));
	return (ptr);
}


char	**ft_new_split(char *s, char c)
{
	char	**ptr;
	int		j;
	int		i;
	int		flag_d = 0;
	int		flag_s = 0;

	ptr = ft_allocation(s, c);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		j = 0;
		if (*s == '"' && flag_s == 0)
		{
			j++;
			flag_d = ft_change_flag(flag_d);
		}
		if (*s == '\'' && flag_d == 0)
		{
			j++;
			flag_s = ft_change_flag(flag_s);
		}
		while ((s[j] && (flag_d == 1 || flag_s == 1)) || (s[j] != '\0' && s[j] != c))
		{
			if (s[j] == '"' && flag_s == 0)
				flag_d = ft_change_flag(flag_d);
			if (s[j] == '\'' && flag_d == 0)
				flag_s = ft_change_flag(flag_s);
			j++;
		}
		printf("j = %d\n", j);
		if (j)
		{
			ptr[i] = ft_substr(s, 0, j);
			printf("line i %s\n", ptr[i]);
			i++;
		}	
		s = s + j;
	}
	return (ptr);
}