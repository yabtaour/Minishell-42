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

int	ft_dollar_len(char *cmd, int i, int type)
{
	int	len = 0;

	// printf("%s\n", cmd);
	// printf("%d\n", i);
	if (type == DOLLAR)
	{
		// printf("len : %d\n", len);
		i++;
		while (cmd[i] != '\0' && cmd[i] != '$' && cmd[i] != ' ' && cmd[i] != '"' && cmd[i] != '\'' && !ft_isdigit(cmd[i]) && cmd[i] != '\n' && cmd[i] != '\\')
		{
			i++;
			len++;
		}
	}
	// printf("%d\n", len);
	return (len);
}

int	ft_add_token(t_data *data, int i, int type)
{
	char	*str;
	int		len;
	int		origin;
	int		idx = 1;

	len = 0;
	origin = i;
	if (type == DOLLAR)
	{
		len = ft_dollar_len(data->cmd, i, type);
		str = malloc(len + 1);
		str[0] = '$';
		origin++;
		while (idx <= len)
		{
			str[idx] = data->cmd[origin];
			idx++;
			origin++;
		}
		str[idx] = '\0';
	}
	else
	{
		len = ft_word_len(data->cmd, i, type);
		str = malloc(len + 1);
		i = 0;
		while (ft_is_right(data->cmd[origin], type))
		{
			str[i] = data->cmd[origin];
			i++;
			origin++;
			if (type == CURLY_BRACKET
				|| type == PARENTHESIS)
				break ;
		}
		str[i] = '\0';
	}
	data->lst_lexer = ft_add_lexer_back(data->lst_lexer, str, type);
	return (origin);
}