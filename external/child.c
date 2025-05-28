/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshawish <sshawish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:23:53 by falhaimo          #+#    #+#             */
/*   Updated: 2025/04/06 14:54:57 by sshawish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_redirection_fork(t_command **command, t_env *env, t_shell *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		set_signal(2);
		preprocess_heredocs(command, env, 1);
		handle_redirection(command, env);
		status = env->exit_status;
		path_error(command, data, env);
		exit(status);
	}
	else if (pid > 0)
	{
		set_signal(3);
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			env->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			env->exit_status = 128 + WTERMSIG(status);
	}
	else
		perror("fork failed");
}

int	setup_child_pipes(t_pipe_data *pipe_data)
{
	if (pipe_data->old_fd != -1 && dup2(pipe_data->old_fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	if (pipe_data->i < pipe_data->num_commands - 1 && dup2(pipe_data->fd[1],
			STDOUT_FILENO) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	if (pipe_data->old_fd != -1)
		close(pipe_data->old_fd);
	if (pipe_data->i < pipe_data->num_commands - 1)
	{
		close(pipe_data->fd[0]);
		close(pipe_data->fd[1]);
	}
	return (0);
}

int	execute_child_command(t_pipe_data *pipe_data)
{
	handle_redirection(&pipe_data->commands[pipe_data->i], pipe_data->env);
	if (pipe_data->env->redir_flag == 1)
		return (1);
	if (is_bulit_in(pipe_data->commands[pipe_data->i]) == 0)
	{
		if (check_cmd(&pipe_data->commands[pipe_data->i], pipe_data->data,
				pipe_data->env) == 1)
			return (1);
		return (1);
	}
	else
	{
		if (execute_command(&pipe_data->commands[pipe_data->i],
				pipe_data->env) == 1)
			return (1);
	}
	exit(EXIT_FAILURE);
}

int	child_process(t_pipe_data *pipe_data)
{
	setup_child_pipes(pipe_data);
	return (execute_child_command(pipe_data));
}

int	execute_cprocess(t_command **command, t_shell *data, t_env *env)
{
	set_signal(1);
	preprocess_heredocs(command, env, 1);
	handle_redirection(command, env);
	if (env->redir_flag == 1 || g_sig == SIGINT
		|| execute_command(command, env) == 1)
		return (1);
	path_error(command, data, env);
	exit(EXIT_FAILURE);
}
