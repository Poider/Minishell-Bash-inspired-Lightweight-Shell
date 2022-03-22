#include "minishell.h"

int ft_lstsize(t_arguments *lst)
{
	int i;
	t_arguments *itering;

	itering = lst;
	i = 0;
	while (itering)
	{
		itering = itering->next;
		i++;
	}
	return (i);
}

char **args_to_table(t_arguments *args)
{
	char **args_array;
	int size;
	int i;

	size = ft_lstsize(args);
	args_array = malloc(sizeof(char *) * (size + 1));
	args_array[size] = 0;
	i = 0;
	while (i < size)
	{
		args_array[i] = args->arg;
		args = args->next;
		i++;
	}
}

int execute(t_line_processing_history *v_lines)
{
	t_commandtable *command_table;
	int id;
	char **args;
	int fd[2];
	int pipe_save;

	pipe_save = 0;
	command_table = v_lines->command_table;
	while (command_table != 0)
	{
		pipe(fd);
		
		id = fork();
		if (id == 0)
		{
			if (pipe_save != 0)
				dup2(pipe_save, 0);
			if(command_table -> input_fd)
				dup2(command_table->input_fd, 0);
			dup2(command_table->output_fd, 1);
			args = args_to_table(command_table->argument);
			// complete
			// check access and execute built in or excve if its not in them
			// for excve args is argument table
			// v_lines->env_vars is env vars table
			// v_lines->exit_status is where to put exit status from waitpid
			free(args);
			close(fd[1]);
			close(fd[0]);
			if (pipe_save != 0 && pipe_save != 1)
				close(pipe_save);
			close_fds(v_lines->command_table);
			return 1;
		}
		if (pipe_save != 0 && pipe_save != 1)
			close(pipe_save);

		//wait(NULL)?!

		close(fd[1]);
		if (command_table->output_fd == 1)
			pipe_save = fd[0];
		else
			pipe_save = 0;
		command_table = command_table->next;
	}
	return 1;
}