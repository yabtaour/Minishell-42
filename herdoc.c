#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

int	herdoc_lent(char *line)
{
	int nbOFherdoc = 0;
	int idx = 0;

	while (line[idx])
	{
		if (line[idx] == '<' && line[idx + 1] == '<')
			nbOFherdoc++;
		idx++;
	}
	return (nbOFherdoc);
}

int herdoc(char *line, int nbOFherdoc)
{
	char	*getline;
	int idx = 0;

	printf("nb of herdoc %d\n", nbOFherdoc);
	while (1)
	{
		if (nbOFherdoc > 0)
			herdoc(line, nbOFherdoc--);
		getline = readline("herdoc>");
		if (!getline)
			return (printf("\n"), 0);
	}
	printf("nb of herdoc %d\n", nbOFherdoc);
	return (0);
}

int main(void)
{
	char *line;
	int idx = 0;

	while (1)
	{
		line = readline("bash :");
		if (!line)
			return 0;
		if (!strncmp(line, "<<", 1)){
			int nbOFherdoc = herdoc_lent(line);
			herdoc(line, nbOFherdoc);}
	}
}