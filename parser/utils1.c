/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falhaimo <falhaimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:30:51 by falhaimo          #+#    #+#             */
/*   Updated: 2025/04/08 21:05:04 by falhaimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error(const char *str)
{
	ft_putstr_fd(str, 2);
	return (1);
}

void	add_redirection(t_command *command, char *filename, int type)
{
	t_redirection	*new_redir;

	new_redir = malloc(sizeof(t_redirection));
	if (!new_redir)
		error("Error: malloc failed\n");
	new_redir->filename = ft_strdup(filename);
	if (!new_redir->filename)
	{
		free(new_redir);
		error("strdup failed\n");
	}
	new_redir->type = type;
	new_redir->heredoc_content = NULL;
	new_redir->next = NULL;
	if (type == 3)
		free_heredoc(new_redir);
	add_redirection_to_command(command, new_redir);
}

void	free_heredoc(t_redirection *new_redir)
{
	if (pipe(new_redir->pipe_fd) == -1)
	{
		free(new_redir->filename);
		free(new_redir);
		error("Error: pipe failed\n");
	}
	close(new_redir->pipe_fd[1]);
	close(new_redir->pipe_fd[0]);
}

void	add_redirection_to_command(t_command *command, t_redirection *new_redir)
{
	t_redirection	*temp;

	if (!command->redirections)
		command->redirections = new_redir;
	else
	{
		temp = command->redirections;
		while (temp->next)
			temp = temp->next;
		temp->next = new_redir;
	}
}
