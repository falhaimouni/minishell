/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falhaimo <falhaimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:32:11 by sshawish          #+#    #+#             */
/*   Updated: 2025/04/08 21:02:31 by falhaimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	just_redirection(t_command **command, t_env *env, t_shell *data)
{
	t_redirection	*redir;

	redir = command[0]->redirections;
	if (redir && (redir->type == 0 || redir->type == 1 || redir->type == 2
			|| redir->type == 3))
	{
		handle_redirection_fork(command, env, data);
	}
}

void	execute_with_redirection(t_command **command, t_shell data, t_env *env)
{
	pid_t	pid;
	int		status;

	set_signal(1);
	pid = fork();
	if (pid == 0)
	{
		set_signal(1);
		preprocess_heredocs(command, env, 1);
		handle_redirection(command, env);
		if (env->redir_flag == 1)
			return ;
		check_cmd(command, data, env);
		path_error(command, &data, env);
		exit(EXIT_SUCCESS);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			env->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			env->exit_status = 128 + WTERMSIG(status);
	}
}

int	execute_single_command(t_command **command, t_shell *data, t_env *env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execute_cprocess(command, data, env) == 1)
			return (1);
	}
	else if (pid > 0)
	{
		set_signal(3);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			env->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			env->exit_status = 128 + WTERMSIG(status);
	}
	else
		perror("fork failed");
	if (g_sig)
		printf("\n");
	return (0);
}

int	handle_single_cmd(t_command **command, t_shell data, t_env *env)
{
	t_redirection	*redir;

	redir = command[0]->redirections;
	if (is_bulit_in(command[0]) == 0)
	{
		if (redir && (redir->type == 0 || redir->type == 1 || redir->type == 2
				|| redir->type == 3))
		{
			execute_with_redirection(command, data, env);
			if (env->redir_flag == 1)
				return (1);
		}
		else if (check_cmd(command, data, env) == 1)
			return (1);
	}
	else
	{
		if (execute_single_command(command, &data, env) == 1)
			return (1);
	}
	return (0);
}

void	execute_commands(t_command **commands, t_shell data, t_env *env,
		int num_commands)
{
	if (check_pipe_syntax(data.user_input, env))
		return ;
	if (check_redirection_syntax(data.user_input, env))
		return ;
	if (num_commands < 1 && commands[0]->cmd == NULL)
	{
		just_redirection(commands, env, &data);
		return ;
	}
	if (num_commands == 1)
	{
		if (handle_single_cmd(commands, data, env) == 1)
		{
			free_heredocs(commands, num_commands);
			free_exit(commands, data, env);
		}
	}
	else
	{
		if (handle_pipe_cmd(commands, data, env, num_commands) == 1)
		{
			free_heredocs(commands, num_commands);
			free_exit(commands, data, env);
		}
	}
}
