#include "../minishell.h"

char	*ft_substr(char *s, int start, size_t len)
{
	char			*ptr;
	unsigned int	i;
	int				end;

	i = 0;
	end = len + start;
	if (!s)
		return (NULL);
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	if (start <= strlen(s))
	{
		while (start < end && s[start] != '\0')
		{
			ptr[i] = s[start];
			i++;
			start++;
		}
	}
	ptr[i] = '\0';
	return (ptr);
}

void	free_split(char **arguments)
{
	int	i;

	i = 0;
	while (arguments[i])
	{
		free(arguments[i]);
		i++;
	}
	free(arguments);
}


char	*ft_join_args(char *s1, char *s2)
{
	char *result;

	result = NULL;
	result = ft_strjoin(s1, " ");
	result = ft_strjoin(result, s2);
	return (result);
}


char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s2)
		return (s1);
	str = malloc(strlen(s1) + strlen(s2) + 1);
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j])
		str[i++] = s2[j++];
	str[strlen(s1) + strlen(s2)] = '\0';
	free(s1);
	return (str);
}

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

static char	**ft_free_tab(char	**str, int i)
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
	ptr = calloc((word_count(s, c) + 1), sizeof(char *));
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