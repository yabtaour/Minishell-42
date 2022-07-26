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
