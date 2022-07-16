#include "../minishell.h"

size_t	word_count(char *s, char c)
{
	
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

	ptr = ft_allocation(s, c);
}