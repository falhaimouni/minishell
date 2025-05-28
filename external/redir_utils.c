/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falhaimo <falhaimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:27:25 by falhaimo          #+#    #+#             */
/*   Updated: 2025/04/08 11:11:35 by falhaimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_redirection(t_command **command, t_env *env)
{
	t_redirection	*redir;

	redir = command[0]->redirections;
	while (redir)
	{
		process_redirection(redir, env);
		if (env->redir_flag == 1)
			return ;
		redir = redir->next;
	}
}

char	*append_char(char *buffer, char c, size_t *buffer_size,
		size_t *buffer_capacity)
{
	char	*new_buffer;

	new_buffer = malloc(*buffer_capacity + 1);
	if (new_buffer == NULL)
	{
		free(buffer);
		return (NULL);
	}
	ft_strlcpy(new_buffer, buffer, *buffer_size + 1);
	new_buffer[*buffer_size] = c;
	free(buffer);
	(*buffer_size)++;
	(*buffer_capacity)++;
	return (new_buffer);
}

char	*process_dollar_sign(t_buffer *buf, char *line, t_env *env, size_t *i)
{
	char	*expanded_line;

	expanded_line = handle_heredoc_dollar(&line[*i], env);
	if (expanded_line)
	{
		buf->content = expand_and_append(buf->content, expanded_line,
				&buf->size, &buf->capacity);
		free(expanded_line);
	}
	while (line[*i] && (line[*i] != ' ' && line[*i] != '\n'))
		(*i)++;
	return (buf->content);
}

char	*process_line(t_buffer *buf, char *line, t_env *env)
{
	size_t	i;
	char	*temp;
	char	*single;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && !env->qouted && line[i + 1] != '$' && line[i + 1])
			buf->content = process_dollar_sign(buf, line, env, &i);
		else
		{
			single = ft_substr(&line[i], 0, 1);
			temp = ft_strjoin(buf->content, single);
			free(buf->content);
			buf->content = temp;
			free(single);
			i++;
		}
	}
	temp = ft_strjoin(buf->content, "\n");
	free(buf->content);
	return (temp);
}
