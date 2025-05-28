/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falhaimo <falhaimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:47:23 by falhaimo          #+#    #+#             */
/*   Updated: 2025/04/08 12:29:43 by falhaimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_pipe(int *fd)
{
	if (pipe(fd) < 0)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

int	handle_pipe_cmd(t_command **commands, t_shell data,
		t_env *env, int num_commands)
{
	t_pipe_data	pipe_data;
	t_pipe_vars	vars;

	vars.i = 0;
	vars.old_fd = -1;
	vars.pid = 0;
	pipe_data.pid = 0;
	preprocess_heredocs(commands, env, num_commands);
	while (vars.i < num_commands && g_sig != SIGINT)
	{
		set_signal(1);
		if (vars.i < num_commands - 1)
			create_pipe(vars.fd);
		pipe_data = (t_pipe_data){vars.i, vars.old_fd, vars.fd, vars.pid,
			commands, data, env, num_commands};
		if (fork_process(&pipe_data, commands) == 1)
			return (1);
		if (vars.i < num_commands - 1)
			vars.old_fd = vars.fd[0];
		vars.i++;
	}
	set_signal(3);
	wait_for_processes(num_commands, env, &pipe_data);
	free_heredocs(commands, num_commands);
	return (0);
}

int	fork_process(t_pipe_data *pipe_data, t_command **command)
{
	(void)command;
	pipe_data->pid = fork();
	if (pipe_data->pid < 0)
	{
		perror("fork");
		return (-1);
	}
	else if (pipe_data->pid == 0)
	{
		if (child_process(pipe_data) == 1)
			return (1);
		if (pipe_data->old_fd != -1)
			close(pipe_data->old_fd);
		if (pipe_data->i < pipe_data->num_commands - 1)
			close(pipe_data->fd[1]);
	}
	else
	{
		if (pipe_data->old_fd != -1)
			close(pipe_data->old_fd);
		if (pipe_data->i < pipe_data->num_commands - 1)
			close(pipe_data->fd[1]);
	}
	return (0);
}

void	wait_for_processes(int num_commands, t_env *env, t_pipe_data *pipe_data)
{
	pid_t		pid;
	int			i;
	int			status;

	i = 0;
	pid = 0;
	while (i < num_commands)
	{
		pid = wait(&status);
		if (pipe_data->pid == pid)
		{
			if (WIFEXITED(status))
				env->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				env->exit_status = 128 + WTERMSIG(status);
		}
		if (g_sig)
			printf("\n");
		i++;
	}
}
