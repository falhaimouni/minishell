/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falhaimo <falhaimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:46:36 by falhaimo          #+#    #+#             */
/*   Updated: 2025/04/08 20:37:52 by falhaimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*allocate_command(void)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	ft_memset(command, 0, sizeof(t_command));
	command->args = malloc(sizeof(char *) * MAX_ARGS);
	if (!command->args)
	{
		free(command);
		return (NULL);
	}
	return (command);
}

int	handle_redirections(char **tokens, int *i, t_command *command)
{
	if (ft_strcmp(tokens[*i], "<") == 0 && tokens[*i + 1])
		add_redirection(command, tokens[++(*i)], 0);
	else if (ft_strcmp(tokens[*i], ">") == 0 && tokens[*i + 1])
		add_redirection(command, tokens[++(*i)], 1);
	else if (ft_strcmp(tokens[*i], ">>") == 0 && tokens[*i + 1])
		add_redirection(command, tokens[++(*i)], 2);
	else if (ft_strcmp(tokens[*i], "<<") == 0 && tokens[*i + 1])
		add_redirection(command, tokens[++(*i)], 3);
	else
		return (0);
	(*i)++;
	return (1);
}

int	handle_argument(char **tokens, int *i, t_command *command, int *count)
{
	if (command->cmd == NULL)
	{
		command->cmd = ft_strdup(tokens[*i]);
		if (!command->cmd)
			return (0);
	}
	else
	{
		command->args[(*count)++] = ft_strdup(tokens[*i]);
		if (!command->args)
			return (0);
	}
	(*i)++;
	return (1);
}

t_command	*parse(char **tokens, int *i)
{
	t_command	*command;
	int			count;

	count = 0;
	command = allocate_command();
	if (!command)
		return (NULL);
	while (tokens[*i])
	{
		if (handle_redirections(tokens, i, command))
			continue ;
		else if (ft_strcmp(tokens[*i], "|") == 0)
		{
			(*i)++;
			break ;
		}
		else
			handle_argument(tokens, i, command, &count);
	}
	command->args[count] = NULL;
	return (command);
}
