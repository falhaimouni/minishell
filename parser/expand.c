/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falhaimo <falhaimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:29:20 by falhaimo          #+#    #+#             */
/*   Updated: 2025/04/08 10:59:14 by falhaimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_numeric_dollar(t_lex *lex)
{
	char	*var_value;

	var_value = NULL;
	if (ft_isdigit(*lex->ptr))
	{
		lex->ptr++;
		var_value = "";
	}
	return (var_value);
}

char	*handle_alnum_dollar(t_lex *lex, t_env *env)
{
	char	*start;
	char	*var_name;
	char	*var_value;
	size_t	name_len;

	start = lex->ptr;
	while (ft_isalnum(*lex->ptr) || *lex->ptr == '_')
		lex->ptr++;
	name_len = lex->ptr - start;
	var_name = ft_substr(start, 0, name_len);
	var_value = get_env_value(env, var_name);
	free(var_name);
	return (var_value);
}

char	*get_var_value(t_lex *lex, t_env *env, bool *free_var)
{
	char	*var_value;

	*free_var = false;
	if (!ft_isalnum(*lex->ptr) && *lex->ptr != '_' && *lex->ptr != '?'
		&& *lex->ptr != '$' && *lex->ptr != '0')
		var_value = "$";
	else if (*lex->ptr == '$' || *lex->ptr == '?' || *lex->ptr == '0')
		var_value = handle_special_dollar(lex, env, free_var);
	else if (ft_isdigit(*lex->ptr))
		var_value = handle_numeric_dollar(lex);
	else
		var_value = handle_alnum_dollar(lex, env);
	if (!var_value)
		var_value = "";
	return (var_value);
}

char	*allocate_new_token(size_t curr_len, size_t var_len,
	char *var_value, bool free_var)
{
	char	*new_token;

	new_token = malloc(curr_len + var_len + 1);
	if (!new_token)
	{
		if (free_var)
			free(var_value);
		return (NULL);
	}
	return (new_token);
}

char	*create_new_token(char *current_token, char *var_value, bool free_var)
{
	char	*new_token;
	size_t	curr_len;
	size_t	var_len;

	if (current_token)
		curr_len = ft_strlen(current_token);
	else
		curr_len = 0;
	var_len = ft_strlen(var_value);
	new_token = allocate_new_token(curr_len, var_len, var_value, free_var);
	if (!new_token)
		return (NULL);
	if (current_token)
	{
		ft_strcpy(new_token, current_token);
		free(current_token);
	}
	else
		new_token[0] = '\0';
	ft_strcat(new_token, var_value);
	if (free_var)
		free(var_value);
	return (new_token);
}
