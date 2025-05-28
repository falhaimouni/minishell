/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshawish <sshawish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:13:41 by falhaimo          #+#    #+#             */
/*   Updated: 2025/03/20 15:47:56 by sshawish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	**allocate_commands_array(int num_commands)
{
	t_command	**commands;

	commands = ft_calloc(num_commands + 1, sizeof(t_command *));
	if (!commands)
		error ("Error: malloc failed\n");
	return (commands);
}

int	count_commands(char **tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!tokens || !tokens[0])
		return (0);
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "|") == 0)
			count++;
		i++;
	}
	return (count + 1);
}

int	parse_commands(char **tokens, t_command **commands, int num_commands)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (count < num_commands)
	{
		commands[count] = parse(tokens, &index);
		if (!commands[count])
		{
			error("Error: parsing command\n");
			return (0);
		}
		count++;
	}
	return (1);
}

void	free_commands(t_command **commands, int num_commands)
{
	int	i;

	i = 0;
	while (i < num_commands)
	{
		free_command(commands[i]);
		i++;
	}
	free(commands);
}

t_command	**parse_all_commands(char **tokens, int *num_commands)
{
	t_command	**commands;

	*num_commands = count_commands(tokens);
	commands = allocate_commands_array(*num_commands);
	if (!commands)
		return (NULL);
	if (!parse_commands(tokens, commands, *num_commands))
	{
		free_commands(commands, *num_commands);
		return (NULL);
	}
	return (commands);
}
