/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falhaimo <falhaimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:19:07 by falhaimo          #+#    #+#             */
/*   Updated: 2025/04/08 13:30:05 by falhaimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_key_value(const char *str, char **key, char **value)
{
	*key = ft_strdup(str);
	if (!*key)
		return (0);
	*value = ft_strchr(*key, '=');
	if (*value)
	{
		*value = *value + 1;
		*(*key + (*value - *key - 1)) = '\0';
	}
	return (1);
}

bool	echo_newline_char(char *args)
{
	int	j;

	j = 1;
	while (args[j] == 'n' || args[j] == 'e' || args[j] == 'E')
		j++;
	return (args[j] == '\0');
}

bool	check_newline(t_command command, int *i)
{
	bool	newline;

	newline = true;
	if (command.args[0] && ft_strcmp(command.args[0], "-") == 0)
		return (newline);
	while (command.args[*i] && command.args[*i][0] == '-'
		&& echo_newline_char(command.args[*i]))
	{
		newline = false;
		(*i)++;
	}
	return (newline);
}

void	print_env(t_env *env, bool is_export)
{
	if (!is_valid_env_var(env->key))
		return ;
	if (is_export)
	{
		if (!env->value)
		{
			printf("export %s\n", env->key);
			return ;
		}
		printf("export %s=\"%s\"\n", env->key, env->value);
	}
	else
		printf("%s=%s\n", env->key, env->value);
}

void	remove_env_variable(char *var, t_env **env)
{
	t_env	*temp;
	t_env	*prev;

	temp = *env;
	prev = NULL;
	while (temp)
	{
		if (ft_strcmp(temp->key, var) == 0)
		{
			if (prev)
				prev->next = temp->next;
			else
				*env = temp->next;
			free(temp->key);
			free(temp->value);
			free(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}
