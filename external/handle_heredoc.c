/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:17:27 by sshawish          #+#    #+#             */
/*   Updated: 2025/03/25 01:22:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	preprocess_heredocs(t_command **commands, t_env *env, int num_commands)
{
	int				i;
	t_redirection	*redir;

	i = 0;
	while (i < num_commands && g_sig != SIGINT)
	{
		redir = commands[i]->redirections;
		while (redir && g_sig != SIGINT)
		{
			if (redir->type == 3)
			{
				redir->heredoc_content = read_heredoc(redir->filename, env);
				if (!redir->heredoc_content)
				{
					perror("heredoc allocation failed");
					exit(1);
				}
			}
			redir = redir->next;
		}
		i++;
	}
}

void	handle_heredoc_redirection(t_redirection *redir)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		perror("pipe failed");
	write(pipe_fd[1], redir->heredoc_content,
		ft_strlen(redir->heredoc_content));
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		perror("dup2 failed");
	close(pipe_fd[0]);
	free(redir->heredoc_content);
	redir->heredoc_content = NULL;
}
