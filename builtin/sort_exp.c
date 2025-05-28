/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falhaimo <falhaimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:03:47 by falhaimo          #+#    #+#             */
/*   Updated: 2025/03/10 11:01:20 by falhaimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_envp_length(t_env *env)
{
	int	len;

	len = 0;
	while (env)
	{
		len++;
		env = env->next;
	}
	return (len);
}

void	swap_env_nodes(t_env *a, t_env *b)
{
	char	*temp_key;
	char	*temp_value;

	temp_value = a->value;
	temp_key = a->key;
	a->key = b->key;
	a->value = b->value;
	b->key = temp_key;
	b->value = temp_value;
}

void	sort_export(t_command cmd, t_env *env)
{
	bool	swapped;
	t_env	*ptr;
	t_env	*last;

	swapped = true;
	last = NULL;
	if (!env || !env->next)
		return ;
	while (swapped)
	{
		swapped = false;
		ptr = env;
		while (ptr->next != last)
		{
			if (ft_strcmp(ptr->key, ptr->next->key) > 0)
			{
				swap_env_nodes(ptr, ptr->next);
				swapped = true;
			}
			ptr = ptr->next;
		}
		last = ptr;
	}
	env_cmd(cmd, env, true);
}

bool	is_valid_env_var_char(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_');
}

bool	is_valid_env_var(const char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (!str)
		return (false);
	if (ft_strchr(str, '='))
	{
		while (str[len] != '=')
			len++;
	}
	if (!((str[0] >= 'a' && str[0] <= 'z')
			|| (str[0] >= 'A' && str[0] <= 'Z') || str[0] == '_'))
		return (false);
	while (i < len)
	{
		if (!is_valid_env_var_char(str[i]))
		{
			write(2, "Invalid character in variable name\n", 35);
			return (false);
		}
		i++;
	}
	return (true);
}
