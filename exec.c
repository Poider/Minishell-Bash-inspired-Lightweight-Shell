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

int number_of_commands(t_commandtable *command_table)
{
	int i;
	
	i = 0;
	while(command_table)
	{
		i++;
		command_table = command_table->next;
	}
	return i;
}

int execute(t_line_processing_history *v_lines)
{
	t_commandtable *command_table;
	char **args;
	int fd[2];
	int pipe_save;
	int out;

	pipe_save = 0;
	command_table = v_lines->command_table;
	v_lines->commands_number =number_of_commands(command_table);
	v_lines->process_id = malloc(sizeof(int) * v_lines->commands_number);
	while (command_table != 0)
	{
		pipe(fd);
		out = fd[1];
		v_lines->process_id[v_lines->iterator++] = fork();
		if (v_lines->process_id[v_lines->iterator - 1] == 0)
		{
			close(fd[0]);
			if (pipe_save != 0)
				dup2(pipe_save, 0);
			if(command_table -> input_fd)
				dup2(command_table->input_fd, 0);
			if (command_table -> output_fd >= 3)
			{
				out = command_table -> output_fd;
			}
			else if (command_table ->next == 0)
				out = 1;
			dup2(out, 1);
			args = args_to_table(command_table->argument);
			// complete
			// check access and execute built in or excve if its not in them
			// for excve args is argument table
			// v_lines->env_vars is env vars table
			// v_lines->exit_status is where to put exit status from waitpid
			return 1;
		}
		if (pipe_save != 0 && pipe_save != 1)
			close(pipe_save);

		close(fd[1]);
		pipe_save = fd[0];
		command_table = command_table->next;
	}
	
	//wait all childreen while none fails
	//children ids are saved in command table process id and number of commands(children) are stored in command_table->commands_number
	return 1;
}
