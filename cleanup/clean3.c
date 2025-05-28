/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falhaimo <falhaimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:25:41 by falhaimo          #+#    #+#             */
/*   Updated: 2025/04/08 20:47:37 by falhaimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cleanup_after_null_tokens(t_shell *data, t_env *env)
{
	free(data->user_input);
	free(env->pwd);
	g_sig = 0;
}

void	cleanup_after_execution(t_shell *data,
		t_command **commands, int num_commands, t_env *env)
{
	int	i;

	g_sig = 0;
	i = 0;
	if (commands && num_commands > 0)
		free_command_redirections(*commands);
	while (i < num_commands)
	{
		free_command(commands[i]);
		i++;
	}
	free(commands);
	if (data->user_input && *data->user_input != '\0'
		&& !ft_is_spaces(data->user_input))
		add_history(data->user_input);
	free_tokens(data);
	free(data->user_input);
	free(env->pwd);
}

t_env	*free_env_list_on_error(t_env *head)
{
	t_env	*current;

	while (head)
	{
		current = head;
		head = head->next;
		free(current->key);
		free(current->value);
		free(current);
	}
	return (NULL);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	path_error(t_command **command, t_shell *data, t_env *env)
{
	if (env->pwd)
		free(env->pwd);
	free_env_list(env);
	just_free(command);
	free_tokens(data);
}
