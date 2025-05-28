/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falhaimo <falhaimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:27:01 by falhaimo          #+#    #+#             */
/*   Updated: 2025/04/08 13:41:33 by falhaimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_or_update_env_var(const char *str, t_env **env)
{
	char	*key;
	char	*value;
	t_env	*tmp;

	if (!parse_key_value(str, &key, &value))
		return ;
	if (value)
		update_or_add_env_node(key, value, env);
	else
	{
		tmp = *env;
		while (tmp)
		{
			if (ft_strcmp(tmp->key, key) == 0)
			{
				free(key);
				return ;
			}
			tmp = tmp->next;
		}
		update_or_add_env_node(key, "", env);
	}
	free(key);
}

t_env	*create_env_node(t_env *temp)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(temp->key);
	if (!new_node->key)
	{
		free(new_node);
		return (NULL);
	}
	if (temp->value)
	{
		new_node->value = ft_strdup(temp->value);
		if (!new_node->value)
		{
			free(new_node->key);
			free(new_node);
			return (NULL);
		}
	}
	else
		new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	handle_no_args(t_command *command, t_env **env)
{
	t_env	*sorted_env;

	sorted_env = copy_env_sort(*env);
	if (!sorted_env)
		return ;
	sort_export(*command, sorted_env);
	free_env_list(sorted_env);
}

void	handle_args(t_command *command, t_env **env, int *status)
{
	int		i;

	i = 0;
	while (command->args[i])
	{
		if (!is_valid_env_var(command->args[i]))
		{
			write(2, "Invalid character in variable name\n", 35);
			*status = 1;
			i++;
			continue ;
		}
		add_or_update_env_var(command->args[i], env);
		i++;
	}
}

void	export_cmd(t_command *command, t_env **env, int *status)
{
	if (!command->args[0])
		handle_no_args(command, env);
	else
		handle_args(command, env, status);
}
