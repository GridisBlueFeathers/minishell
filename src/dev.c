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
	int	i;

	i = 0;
	while (data(GET)->prompt[i])
	{
		printf("Prompt %d: %s\n", i, data(GET)->prompt[i]->name);
		i++;
	}
}
