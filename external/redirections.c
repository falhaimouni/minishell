/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falhaimo <falhaimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:11:23 by sshawish          #+#    #+#             */
/*   Updated: 2025/04/07 14:20:03 by falhaimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_redirection_file(const char *filename, int flags, t_env *env)
{
	int	fd;

	fd = open(filename, flags, 0644);
	if (fd < 0)
	{
		perror(filename);
		env->redir_flag = 1;
		env->exit_status = 1;
		return (-1);
	}
	return (fd);
}

void	handle_input_redirection(const char *input, t_env *env)
{
	int	fd;

	fd = open_redirection_file(input, O_RDONLY, env);
	if (fd == -1)
		return ;
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	handle_output_redirection(const char *output, t_env *env)
{
	int	fd;

	fd = open_redirection_file(output, O_WRONLY | O_CREAT | O_TRUNC, env);
	if (fd == -1)
		return ;
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_append_redirection(const char *output, t_env *env)
{
	int	fd;

	fd = open_redirection_file(output, O_WRONLY | O_CREAT | O_APPEND, env);
	if (fd == -1)
		return ;
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	process_redirection(t_redirection *redir, t_env *env)
{
	if (redir->type == 3 && redir->heredoc_content)
	{
		handle_heredoc_redirection(redir);
		if (env->redir_flag == 1)
			return ;
	}
	else if (redir->type == 0)
	{
		handle_input_redirection(redir->filename, env);
		if (env->redir_flag == 1)
			return ;
	}
	else if (redir->type == 1)
	{
		handle_output_redirection(redir->filename, env);
		if (env->redir_flag == 1)
			return ;
	}
	else if (redir->type == 2)
	{
		handle_append_redirection(redir->filename, env);
		if (env->redir_flag == 1)
			return ;
	}
}
