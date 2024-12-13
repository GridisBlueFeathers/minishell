#include "libft/stdlib.h"
#include "minishell.h"

void	dev_mock_cat_make(void)
{
	data(GET)->cmd_amount = 1;
	data(GET)->commands = (t_cmd **)ft_calloc(2, sizeof(t_cmd *));
	data(GET)->commands[0] = ft_calloc(1, sizeof(t_cmd));
	data(GET)->commands[0]->bin = ft_strdup("/usr/bin/cat");
	data(GET)->commands[0]->name = ft_strdup("cat");
	char	*argv[] = {"cat", "Makefile", NULL};
	data(GET)->commands[0]->argv = ft_strarrdup(argv);
	data(GET)->commands[0]->type = BIN;
	data(GET)->commands[0]->index = 0;
	data(GET)->commands[0]->redir_valid = 1;
}

void	dev_mock_echo_hi(void)
{
	data(GET)->cmd_amount = 1;
	data(GET)->commands = (t_cmd **)ft_calloc(2, sizeof(t_cmd *));
	data(GET)->commands[0] = ft_calloc(1, sizeof(t_cmd));
	data(GET)->commands[0]->bin = ft_strdup("/usr/bin/echo");
	data(GET)->commands[0]->name = ft_strdup("echo");
	char	*argv[] = {"echo", "hi", NULL};
	data(GET)->commands[0]->argv = ft_strarrdup(argv);
	data(GET)->commands[0]->type = BIN;
	data(GET)->commands[0]->index = 0;
	data(GET)->commands[0]->redir_valid = 1;
}
