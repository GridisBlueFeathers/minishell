#include "libft/stdlib.h"
#include "minishell.h"

void	dev_mock_cat_heredoc(void)
{
	data(GET)->cmd_amount = 1;
	data(GET)->commands = (t_cmd **)ft_calloc(2, sizeof(t_cmd *));
	data(GET)->commands[0] = ft_calloc(1, sizeof(t_cmd));
	data(GET)->commands[0]->name = ft_strdup("cat");
	char	*argv[] = {"cat", NULL};
	data(GET)->commands[0]->argv = ft_strarrdup(argv);
	data(GET)->commands[0]->type = BIN;
	data(GET)->commands[0]->index = 0;
	data(GET)->commands[0]->redir_valid = 1;
	data(GET)->commands[0]->redir_head = ft_calloc(1, sizeof(t_redir));
	data(GET)->commands[0]->redir_tail = data(GET)->commands[0]->redir_head;
	data(GET)->commands[0]->redir_head->heredoc_delim = ft_strdup("hey");
	data(GET)->commands[0]->redir_head->type = HEREDOC;
}

void	dev_mock_cat_make(void)
{
	data(GET)->cmd_amount = 1;
	data(GET)->commands = (t_cmd **)ft_calloc(2, sizeof(t_cmd *));
	data(GET)->commands[0] = ft_calloc(1, sizeof(t_cmd));
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
	data(GET)->commands[0]->name = ft_strdup("cat");
	char	*argv_0[] = {"cat", "dev/2", NULL};
	data(GET)->commands[0]->argv = ft_strarrdup(argv_0);
	data(GET)->commands[0]->type = BIN;
	data(GET)->commands[0]->index = 0;
	data(GET)->commands[0]->redir_valid = 1;

	data(GET)->commands[1] = ft_calloc(1, sizeof(t_cmd));
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
	data(GET)->commands[0]->name = ft_strdup("cat");
	char	*argv_0[] = {"cat", "dev/2", NULL};
	data(GET)->commands[0]->argv = ft_strarrdup(argv_0);
	data(GET)->commands[0]->type = BIN;
	data(GET)->commands[0]->index = 0;
	data(GET)->commands[0]->redir_valid = 1;

	data(GET)->commands[1] = ft_calloc(1, sizeof(t_cmd));
	data(GET)->commands[1]->name = ft_strdup("grep");
	char	*argv_1[] = {"grep", "hey", NULL};
	data(GET)->commands[1]->argv = ft_strarrdup(argv_1);
	data(GET)->commands[1]->type = BIN;
	data(GET)->commands[1]->index = 1;
	data(GET)->commands[1]->redir_valid = 1;

	data(GET)->commands[2] = ft_calloc(1, sizeof(t_cmd));
	data(GET)->commands[2]->name = ft_strdup("wc");
	char	*argv_2[] = {"wc", "-l", NULL};
	data(GET)->commands[2]->argv = ft_strarrdup(argv_2);
	data(GET)->commands[2]->type = BIN;
	data(GET)->commands[2]->index = 2;
	data(GET)->commands[2]->redir_valid = 1;
}

static void	dev_mock_cat_dev_input(void)
{
	data(GET)->cmd_amount = 1;
	data(GET)->commands = (t_cmd **)ft_calloc(2, sizeof(t_cmd *));
	data(GET)->commands[0] = ft_calloc(1, sizeof(t_cmd));
	data(GET)->commands[0]->name = ft_strdup("cat");
	char	*argv_0[] = {"cat", NULL};
	data(GET)->commands[0]->argv = ft_strarrdup(argv_0);
	data(GET)->commands[0]->type = BIN;
	data(GET)->commands[0]->index = 0;
	data(GET)->commands[0]->redir_valid = 1;
	data(GET)->commands[0]->redir_head = ft_calloc(1, sizeof(t_redir));
	data(GET)->commands[0]->redir_tail = data(GET)->commands[0]->redir_head;
	data(GET)->commands[0]->redir_head->file_name = ft_strdup("dev/input");
	data(GET)->commands[0]->redir_head->type = INPUT;
}

static void	dev_mock_cat(void)
{
	data(GET)->cmd_amount = 1;
	data(GET)->commands = (t_cmd **)ft_calloc(2, sizeof(t_cmd *));
	data(GET)->commands[0] = ft_calloc(1, sizeof(t_cmd));
	data(GET)->commands[0]->name = ft_strdup("cat");
	char	*argv_0[] = {"cat", NULL};
	data(GET)->commands[0]->argv = ft_strarrdup(argv_0);
	data(GET)->commands[0]->type = BIN;
	data(GET)->commands[0]->index = 0;
	data(GET)->commands[0]->redir_valid = 1;
}

static void	dev_mock_qwerty(void)
{
	data(GET)->cmd_amount = 1;
	data(GET)->commands = (t_cmd **)ft_calloc(2, sizeof(t_cmd *));
	data(GET)->commands[0] = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	data(GET)->commands[0]->name = ft_strdup("qwerty");
	char	*argv_0[] = {"qwerty", NULL};
	data(GET)->commands[0]->argv = ft_strarrdup(argv_0);
	data(GET)->commands[0]->type = BIN;
	data(GET)->commands[0]->index = 0;
	data(GET)->commands[0]->redir_valid = 1;
}

static void	dev_mock_hello(void)
{
	data(GET)->cmd_amount = 1;
	data(GET)->commands = (t_cmd **)ft_calloc(2, sizeof(t_cmd *));
	data(GET)->commands[0] = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	data(GET)->commands[0]->name = ft_strdup("hello");
	char	*argv_0[] = {"hello", NULL};
	data(GET)->commands[0]->argv = ft_strarrdup(argv_0);
	data(GET)->commands[0]->type = BIN;
	data(GET)->commands[0]->index = 0;
	data(GET)->commands[0]->redir_valid = 1;
}

static void	dev_mock_asdf(void)
{
	data(GET)->cmd_amount = 1;
	data(GET)->commands = (t_cmd **)ft_calloc(2, sizeof(t_cmd *));
	data(GET)->commands[0] = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	data(GET)->commands[0]->name = ft_strdup("asdf");
	char	*argv_0[] = {"asdf", NULL};
	data(GET)->commands[0]->argv = ft_strarrdup(argv_0);
	data(GET)->commands[0]->type = BIN;
	data(GET)->commands[0]->index = 0;
	data(GET)->commands[0]->redir_valid = 1;
}

static void	dev_mock_absolute_asdf(void)
{
	data(GET)->cmd_amount = 1;
	data(GET)->commands = (t_cmd **)ft_calloc(2, sizeof(t_cmd *));
	data(GET)->commands[0] = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	data(GET)->commands[0]->name = ft_strdup("./asdf");
	char	*argv_0[] = {"./asdf", NULL};
	data(GET)->commands[0]->argv = ft_strarrdup(argv_0);
	data(GET)->commands[0]->type = BIN;
	data(GET)->commands[0]->index = 0;
	data(GET)->commands[0]->redir_valid = 1;
}

void	dev_shim_prompt()
{
	if (!ft_strcmp(data(GET)->rl_prompt, "cat Makefile"))
		dev_mock_cat_make();	
	if (!ft_strcmp(data(GET)->rl_prompt, "cat << hey"))
		dev_mock_cat_heredoc();	
	if (!ft_strcmp(data(GET)->rl_prompt, "echo hi"))
		dev_mock_echo_hi();	
	if (!ft_strcmp(data(GET)->rl_prompt, "cat dev/2 | grep hey | wc -l"))
		dev_mock_cat_pipe_grep_pipe_wc();	
	if (!ft_strcmp(data(GET)->rl_prompt, "cat dev/2 | grep hey"))
		dev_mock_cat_pipe_grep();	
	if (!ft_strcmp(data(GET)->rl_prompt, "cat dev/2"))
		dev_mock_cat_dev2();	
	if (!ft_strcmp(data(GET)->rl_prompt, "cat < dev/input"))
		dev_mock_cat_dev_input();	
	if (!ft_strcmp(data(GET)->rl_prompt, "cat"))
		dev_mock_cat();
	if (!ft_strcmp(data(GET)->rl_prompt, "qwerty"))
		dev_mock_qwerty();
	if (!ft_strcmp(data(GET)->rl_prompt, "hello"))
		dev_mock_hello();
	if (!ft_strcmp(data(GET)->rl_prompt, "asdf"))
		dev_mock_asdf();
	if (!ft_strcmp(data(GET)->rl_prompt, "./asdf"))
		dev_mock_absolute_asdf();
}
