#include "../minishell.h"

/// had lfunction katakhud string wtype dyalha w katsab bihom node jdida

t_lexer	*ft_new_lexer_node(char *str, int type)
{
	t_lexer	*node;
	int		i;

	node = NULL;
	if (!str)
		return (NULL);
	i = strlen(str);
	node = malloc(sizeof(t_lexer));
	if (!node)
		return (NULL);
	node->value = malloc(i + 1);
	i = -1;
	while (str[++i])
		node->value[i] = str[i];
	node->value[i] = '\0';
	node->type = type;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

/// had lfunction katakhoud list dyal lexer w string li ghatzid w type dyalha
/// kat3yt lfunction li katsawb node
/// ila kant list khawya katreturni node li sawbat
/// ila kant list 3amra katb9a ghada 7tal llkhr dyalha w katajouter node jdida then katreturni list kamla

t_lexer	*ft_add_lexer_back(t_lexer *lexer, char *str, int type)
{
	t_lexer	*node;
	t_lexer	*lexer_clone;

	if (!str)
		return (NULL);
	node = ft_new_lexer_node(str, type);
	if (!node)
		return (NULL);
	if (lexer == NULL)
		return (node);
	lexer_clone = lexer;
	while (lexer_clone->next != NULL)
		lexer_clone = lexer_clone->next;
	lexer_clone->next = node;
	node->prev = lexer_clone;
	return (lexer);
}

/// had lfunction kattakhoud l'index dyal data->cmd[i] w type dyal dak lcaracter
/// katb9a checki dakchi li morah
/// kat7bs mli katwsli lchi caracter type dyalou mkhtalf
/// then kat3eyt lfunction li katzid dik lpart flist
