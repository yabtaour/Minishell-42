#include "../minishell.h"

int	ft_get_in(int *fd, int *red, int red_num)
{
	int	fd_in;
	int	i;

	fd_in = 0;
	i = 0;
	while (i < red_num)
	{
		if (red[i] == 3)
			fd_in = fd[i];
		i++;
	}
	return (fd_in);
}

int	ft_get_out(int *fd, int *red, int red_num)
{
	int	fd_out;
	int	i;

	fd_out = 1;
	i = 0;
	while (i < red_num)
	{
		if (red[i] == 1 || red[i] == 2)
			fd_out = fd[i];
		i++;
	}
	return (fd_out);
}