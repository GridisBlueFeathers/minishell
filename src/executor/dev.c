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

void	dev_mock_cat_dev2(void)
{
	data(GET)->cmd_amount = 1;
	data(GET)->commands = (t_cmd **)ft_calloc(2, sizeof(t_cmd *));
	data(GET)->commands[0] = ft_calloc(1, sizeof(t_cmd));
	data(GET)->commands[0]->bin = ft_strdup("/usr/bin/cat");
	data(GET)->commands[0]->name = ft_strdup("cat");
	char	*argv_0[] = {"cat", "dev/2", NULL};
	data(GET)->commands[0]->argv = ft_strarrdup(argv_0);
	data(GET)->commands[0]->type = BIN;
	data(GET)->commands[0]->index = 0;
	data(GET)->commands[0]->redir_valid = 1;
}

void	dev_mock_cat_pipe_grep(void)
{
	data(GET)->cmd_amount = 2;
	data(GET)->commands = (t_cmd **)ft_calloc(3, sizeof(t_cmd *));
	data(GET)->commands[0] = ft_calloc(1, sizeof(t_cmd));
	data(GET)->commands[0]->bin = ft_strdup("/usr/bin/cat");
	data(GET)->commands[0]->name = ft_strdup("cat");
	char	*argv_0[] = {"cat", "dev/2", NULL};
	data(GET)->commands[0]->argv = ft_strarrdup(argv_0);
	data(GET)->commands[0]->type = BIN;
	data(GET)->commands[0]->index = 0;
	data(GET)->commands[0]->redir_valid = 1;

	data(GET)->commands[1] = ft_calloc(1, sizeof(t_cmd));
	data(GET)->commands[1]->bin = ft_strdup("/usr/bin/grep");
	data(GET)->commands[1]->name = ft_strdup("grep");
	char	*argv_1[] = {"grep", "hey", NULL};
	data(GET)->commands[1]->argv = ft_strarrdup(argv_1);
	data(GET)->commands[1]->type = BIN;
	data(GET)->commands[1]->index = 1;
	data(GET)->commands[1]->redir_valid = 1;
}

void	dev_mock_cat_pipe_grep_pipe_wc(void)
{
	data(GET)->cmd_amount = 3;
	data(GET)->commands = (t_cmd **)ft_calloc(4, sizeof(t_cmd *));

	data(GET)->commands[0] = ft_calloc(1, sizeof(t_cmd));
	data(GET)->commands[0]->bin = ft_strdup("/usr/bin/cat");
	data(GET)->commands[0]->name = ft_strdup("cat");
	char	*argv_0[] = {"cat", "dev/2", NULL};
	data(GET)->commands[0]->argv = ft_strarrdup(argv_0);
	data(GET)->commands[0]->type = BIN;
	data(GET)->commands[0]->index = 0;
	data(GET)->commands[0]->redir_valid = 1;

	data(GET)->commands[1] = ft_calloc(1, sizeof(t_cmd));
	data(GET)->commands[1]->bin = ft_strdup("/usr/bin/grep");
	data(GET)->commands[1]->name = ft_strdup("grep");
	char	*argv_1[] = {"grep", "hey", NULL};
	data(GET)->commands[1]->argv = ft_strarrdup(argv_1);
	data(GET)->commands[1]->type = BIN;
	data(GET)->commands[1]->index = 1;
	data(GET)->commands[1]->redir_valid = 1;

	data(GET)->commands[2] = ft_calloc(1, sizeof(t_cmd));
	data(GET)->commands[2]->bin = ft_strdup("/usr/bin/wc");
	data(GET)->commands[2]->name = ft_strdup("wc");
	char	*argv_2[] = {"wc", "-l", NULL};
	data(GET)->commands[2]->argv = ft_strarrdup(argv_2);
	data(GET)->commands[2]->type = BIN;
	data(GET)->commands[2]->index = 2;
	data(GET)->commands[2]->redir_valid = 1;
}
