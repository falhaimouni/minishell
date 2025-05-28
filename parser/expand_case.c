/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_case.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falhaimo <falhaimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:35:19 by falhaimo          #+#    #+#             */
/*   Updated: 2025/04/07 15:59:45 by falhaimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_value(t_env *env, char *var_name)
{
	while (env)
	{
		if (ft_strcmp(env->key, var_name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*get_shell_pid(void)
{
	int		fd;
	int		i;
	char	buffer[256];
	char	*pid_str;

	i = 0;
	fd = open("/proc/self/stat", O_RDONLY);
	if (fd < 0)
		return (NULL);
	read(fd, buffer, sizeof(buffer) - 1);
	close(fd);
	buffer[sizeof(buffer) - 1] = '\0';
	while (buffer[i] && buffer[i] != ' ')
		i++;
	buffer[i] = '\0';
	pid_str = ft_strdup(buffer);
	if (!pid_str)
		return (NULL);
	return (pid_str);
}

char	*remove_extra_spaces(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = malloc(ft_strlen(str) + 1);
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == ' ' && (i == 0 || str[i + 1] == '\0'
				|| str[i + 1] == ' '))
			i++;
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*handle_dsign(t_lex *lex, bool *free_var)
{
	char	*var_value;

	*free_var = false;
	lex->ptr++;
	var_value = get_shell_pid();
	*free_var = true;
	return (var_value);
}

char	*handle_special_dollar(t_lex *lex, t_env *env, bool *free_var)
{
	char	*var_value;

	var_value = NULL;
	if (*lex->ptr == '$')
		var_value = handle_dsign(lex, free_var);
	else if (*lex->ptr == '?')
	{
		lex->ptr++;
		if (g_sig)
		{
			var_value = ft_itoa(130);
			g_sig = 0;
		}
		else
			var_value = ft_itoa(env->exit_status);
		*free_var = true;
	}
	else if (*lex->ptr == '0')
	{
		lex->ptr++;
		var_value = "minishell";
	}
	return (var_value);
}
