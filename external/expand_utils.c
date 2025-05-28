/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falhaimo <falhaimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:21:20 by falhaimo          #+#    #+#             */
/*   Updated: 2025/04/08 11:12:41 by falhaimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_variable_value(char *var_name, t_env *env)
{
	char	*var_value;

	if (ft_strcmp(var_name, "$$") == 0)
		var_value = get_shell_pid();
	else if (ft_strcmp(var_name, "0") == 0)
		var_value = "minishell";
	else
		var_value = get_env_value(env, var_name);
	return (var_value);
}

char	*expand_variable(char *start, t_env *env, size_t *i)
{
	char	*var_name;
	char	*var_value;
	char	*expanded;

	if (!ft_isalnum(*start) && *start != '_'
		&& *start != '$' && *start != '0')
		return (ft_strdup("$"));
	var_name = get_var_name(start, i);
	var_value = get_variable_value(var_name, env);
	if (var_value)
	{
		expanded = ft_strdup(var_value);
		if (!expanded)
			return (NULL);
	}
	else
	{
		expanded = ft_strdup("");
		if (!expanded)
			return (NULL);
	}
	free(var_name);
	return (expanded);
}

char	*expand_dollar_in_line(char *line, t_env *env,
		size_t *i, char *new_line)
{
	char	*expanded;

	expanded = expand_variable(&line[*i + 1], env, i);
	if (!expanded)
	{
		free(new_line);
		return (NULL);
	}
	new_line = ft_strjoin_free(new_line, expanded);
	free(expanded);
	return (new_line);
}

char	*handle_heredoc_dollar(char *line, t_env *env)
{
	char	*new_line;
	char	c[2];
	size_t	i;

	i = 0;
	new_line = ft_strdup("");
	if (!new_line)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '$')
			new_line = expand_dollar_in_line(line, env, &i, new_line);
		else
		{
			c[0] = line[i];
			c[1] = '\0';
			new_line = ft_strjoin_free(new_line, c);
			i++;
		}
		if (!new_line)
			return (NULL);
	}
	return (new_line);
}

char	*expand_and_append(char *buffer, char *expanded_line,
		size_t *buffer_size, size_t *buffer_capacity)
{
	char	*new_buffer;
	size_t	expanded_len;

	expanded_len = ft_strlen(expanded_line) + 1;
	new_buffer = ft_strjoin(buffer, expanded_line);
	free(buffer);
	*buffer_capacity += expanded_len;
	*buffer_size += expanded_len;
	return (new_buffer);
}
