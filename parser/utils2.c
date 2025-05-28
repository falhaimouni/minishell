/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falhaimo <falhaimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:39:18 by falhaimo          #+#    #+#             */
/*   Updated: 2025/04/08 10:35:36 by falhaimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*process_quotes(t_lex *lex)
{
	if (lex->in_quotes && *lex->ptr == lex->quote_char)
	{
		lex->in_quotes = false;
		lex->quote_char = '\0';
	}
	else if (!lex->in_quotes)
	{
		lex->in_quotes = true;
		lex->quote_char = *lex->ptr;
	}
	else
		lex->current_token = add_tokens(lex->ptr, lex->current_token);
	return (lex->current_token);
}

char	*process_dollar(t_lex *lex, t_env *env)
{
	lex->current_token = handle_dollar(lex, env, lex->in_quotes);
	lex->ptr--;
	return (lex->current_token);
}

char	*process_char(t_lex *lex, const char *del, t_env *env)
{
	if (*lex->ptr == '\"' || *lex->ptr == '\'')
	{
		env->qouted = 1;
		return (process_quotes(lex));
	}
	if (*lex->ptr == '$' && !lex->in_heredoc && (!lex->in_quotes
			|| (lex->in_quotes && lex->quote_char == '\"')))
		return (process_dollar(lex, env));
	else if (check_op(lex) && !lex->in_quotes)
		handle_op(lex);
	else if (is_delimiter(*lex->ptr, del) && !lex->in_quotes)
	{
		if (lex->current_token)
			return (lex->current_token);
	}
	else
		lex->current_token = add_tokens(lex->ptr, lex->current_token);
	return (lex->current_token);
}

char	*handle_dollar(t_lex *lex, t_env *env, bool in_double_quotes)
{
	char	*var_value;
	char	*new_token;
	char	*str;
	bool	free_var;

	lex->ptr++;
	var_value = get_var_value(lex, env, &free_var);
	new_token = create_new_token(lex->current_token, var_value, free_var);
	if (!new_token)
		return (NULL);
	lex->current_token = new_token;
	if (!in_double_quotes)
	{
		str = remove_extra_spaces(new_token);
		free(new_token);
		lex->current_token = str;
		return (str);
	}
	return (new_token);
}
