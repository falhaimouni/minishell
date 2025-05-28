/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falhaimo <falhaimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:03:48 by falhaimo          #+#    #+#             */
/*   Updated: 2025/04/07 15:27:05 by falhaimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_exit(t_command **commands, t_shell data, t_env *env)
{
	int	status;

	status = env->exit_status;
	path_error(commands, &data, env);
	exit(status);
}

void	just_free(t_command **commands)
{
	int	i;

	if (!commands)
		return ;
	i = 0;
	while (commands[i])
	{
		free_command(commands[i]);
		i++;
	}
	free(commands);
}

void	free_heredocs(t_command **commands, int num_commands)
{
	int	i;

	i = 0;
	while (i < num_commands)
	{
		free_heredoc_content(commands[i]);
		i++;
	}
}

void	free_split_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		tmp->key = NULL;
		free(tmp->value);
		tmp->value = NULL;
		free(tmp);
		tmp = NULL;
	}
}
