/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falhaimo <falhaimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:21:46 by falhaimo          #+#    #+#             */
/*   Updated: 2025/04/08 11:18:35 by falhaimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	prepare_arguments(t_command *command, char ***argv)
{
	int	arg_count;
	int	i;

	arg_count = 0;
	i = 0;
	while (command->args[arg_count] != NULL)
		arg_count++;
	*argv = malloc(sizeof(char *) * (arg_count + 2));
	if (!*argv)
		error("malloc failed\n");
	(*argv)[0] = command->cmd;
	while (i < arg_count)
	{
		(*argv)[i + 1] = command->args[i];
		i++;
	}
	(*argv)[arg_count + 1] = NULL;
}

char	*initialize_buffer(char *buffer, size_t *size, size_t *buffer_capacity)
{
	if (buffer == NULL)
	{
		*buffer_capacity = 1;
		buffer = malloc(*buffer_capacity);
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	else
	{
		*size = ft_strlen(buffer);
		*buffer_capacity = *size + 1;
	}
	return (buffer);
}

char	*heredoc_read_lines(t_buffer *buf, const char *del, t_env *env, int tmp)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp((char *)line, (char *)del) == 0)
		{
			free(line);
			break ;
		}
		buf->content = process_line(buf, line, env);
		free(line);
	}
	if (g_sig == SIGINT)
	{
		dup2(tmp, STDIN_FILENO);
		env->exit_status = 130;
	}
	return (buf->content);
}

char	*read_heredoc_loop(char *buffer, const char *delimiter, t_env *env)
{
	int			tmp;
	t_buffer	buf;

	tmp = dup(STDIN_FILENO);
	buf.size = 0;
	buf.content = initialize_buffer(NULL, &buf.size, &buf.capacity);
	if (!buf.content)
		return (NULL);
	set_signal(2);
	buffer = heredoc_read_lines(&buf, delimiter, env, tmp);
	close(tmp);
	return (buffer);
}

char	*read_heredoc(const char *delimiter, t_env *env)
{
	char	*buffer;

	buffer = NULL;
	buffer = read_heredoc_loop(buffer, delimiter, env);
	return (buffer);
}
