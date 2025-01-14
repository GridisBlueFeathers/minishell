#include "minishell.h"

void	env_print(void)
{
	t_env_var	*node;

	node = data(GET)->env.first;
	while (node)
	{
		printf("%s\n", node->key);
		printf("%s\n\n", node->value);
		node = node->next;
	}
}

void	tokenizer_print()
{
	t_token	*token;
	int	i;

	i = 0;
	while (data(GET)->prompt[i])
	{
		token = data(GET)->prompt[i]->first;
		printf("Prompt %d: %s\n", i, data(GET)->prompt[i]->name);
		while (token)
		{
			printf("Token Index: %zu\n", token->idx);
			if (token->tok_type == APPEND)
				printf("Token Type: APPEND\n");
			else if (token->tok_type == HEREDOC)
				printf("Token Type: HEREDOC\n");
			else if (token->tok_type == OUTPUT)
				printf("Token Type: OUTPUT\n");
			else if (token->tok_type == INPUT)
				printf("Token Type: INPUT\n");
			else
				printf("Token Type: WORD\n");
			printf("Token String: %s\n\n", token->tok_str);
			token = token->next;
		}
		i++;
	}
}

void	debug_print(void)	
{
	printf("debug\n");
	//env_print();
	tokenizer_print();
}
