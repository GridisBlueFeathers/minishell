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
			else if (token->tok_type == CMD)
				printf("Token Type: CMD\n");
			else
				printf("Token Type: WORD\n");
			printf("Token String: %s\n\n", token->tok_str);
			token = token->next;
		}
		i++;
	}
}

void	redir_print(t_redir *redir)
{
	while (redir)
	{
		printf("---> Redir for the Command\n");
		if (redir->type == APPEND)
			printf("Redir Type: APPEND\n");
		else if (redir->type == HEREDOC)
		{
			printf("Redir Type: HEREDOC\n");
			printf("Heredoc Delimiter: %s\n", redir->heredoc_delim);
			if (redir->heredoc_expand)
				printf("Heredoc needs to expand\n");
			else
				printf("Heredoc does NOT need to expand\n");
		}
		else if (redir->type == OUTPUT)
			printf("Redir Type: OUTPUT\n");
		else
			printf("Redir Type: INPUT\n");
		printf("Redir File Name: %s\n", redir->file_name);
		if (redir->fd == 1)
			printf("Redir FD: STDOUT_FILENO\n");
		else if (redir->fd == 0)
			printf("Redir FD: STDIN_FILENO\n");
		else
			printf("Redir FD: %d\n", redir->fd);
		redir = redir->next;
	}
}

void	command_table_print(void)
{
	int		i;

	i = 0;
	while (data(GET)->commands[i])
	{
		printf("Command %d\n", i);
		if (data(GET)->commands[i]->type == BUILTIN)
			printf("Command Type: BUILTIN\n");
		else
			printf("Command Type: BIN\n");
		printf("Command Name: %s\n", data(GET)->commands[i]->name);
		printf("Command Arguments: \n");
		ft_putstrarr_fd(data(GET)->commands[i]->argv, STDOUT_FILENO);
		printf("\nCommand Bin: %s\n", data(GET)->commands[i]->bin);
		if (data(GET)->commands[i]->redir_head)
			redir_print(data(GET)->commands[i]->redir_head);
		printf("\n");
		i++;
	}
}

void	debug_print(void)	
{
	printf("--------------------------\ndebug\n--------------------------\n");
	//env_print();
	tokenizer_print();
	command_table_print();
}
