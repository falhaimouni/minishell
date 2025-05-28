/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falhaimo <falhaimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 14:07:46 by falhaimo          #+#    #+#             */
/*   Updated: 2025/04/07 15:26:18 by falhaimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_heredoc_content(t_command *command)
{
	t_redirection	*redir;

	if (!command || !command->redirections)
		return ;
	redir = command->redirections;
	while (redir)
	{
		if (redir->heredoc_content != NULL)
		{
			free(redir->heredoc_content);
			redir->heredoc_content = NULL;
		}
		redir = redir->next;
	}
}

void	free_redirection(t_redirection *redir)
{
	t_redirection	*temp;

	if (redir)
	{
		while (redir)
		{
			temp = redir;
			redir = redir->next;
			if (temp->filename)
				free(temp->filename);
			free(temp);
		}
	}
}

void	free_command_redirections(t_command *command)
{
	if (command->redirections)
	{
		free_redirection(command->redirections);
		command->redirections = NULL;
	}
}

void	free_tokens(t_shell *data)
{
	int	j;

	j = 0;
	while (data->tokens[j])
	{
		free(data->tokens[j]);
		j++;
	}
	free(data->tokens);
}

void	free_command(t_command *command)
{
	int	i;

	i = 0;
	if (!command)
		return ;
	if (command->cmd)
		free(command->cmd);
	if (command->args)
	{
		while (command->args[i])
		{
			free(command->args[i]);
			i++;
		}
		free(command->args);
	}
	free_command_redirections(command);
	free(command);
}
