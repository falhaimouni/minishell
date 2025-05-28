/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falhaimo <falhaimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 14:03:47 by falhaimo          #+#    #+#             */
/*   Updated: 2025/03/12 11:12:22 by falhaimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*add_tokens(char *ptr, char *current_token)
{
	size_t		len;
	char		*new_token;

	len = 0;
	if (current_token)
		len = ft_strlen(current_token);
	new_token = malloc(len + 2);
	if (!new_token)
		return (NULL);
	if (current_token)
	{
		ft_strcpy(new_token, current_token);
		free(current_token);
	}
	new_token[len] = *ptr;
	new_token[len + 1] = '\0';
	return (new_token);
}

bool	initialize_tokenization(char *input, t_lex *lex, int count)
{
	if (!closed_quotes(input))
	{
		printf("Error: unclosed quotes.\n");
		return (false);
	}
	(void)count;
	lex->tokens = malloc(sizeof(char *) * (ft_strlen(input) + 1));
	if (!lex->tokens)
		return (false);
	lex->ptr = input;
	lex->i = 0;
	lex->in_heredoc = 0;
	lex->quote_char = '\0';
	lex->in_quotes = false;
	lex->current_token = NULL;
	return (true);
}

char	**extract_tokens(char *input, const char *del, int count, t_env *env)
{
	t_lex	lex;

	if (!initialize_tokenization(input, &lex, count))
		return (NULL);
	env->qouted = 0;
	while (*lex.ptr)
	{
		lex.current_token = process_char(&lex, del, env);
		if (lex.current_token && is_delimiter(*lex.ptr, del) && !lex.in_quotes)
		{
			lex.tokens[lex.i++] = lex.current_token;
			lex.current_token = NULL;
		}
		lex.ptr++;
	}
	if (lex.current_token)
		lex.tokens[lex.i++] = lex.current_token;
	lex.tokens[lex.i] = NULL;
	return (lex.tokens);
}

char	**lexing(t_shell *data, t_env *env)
{
	const char	*delimiters;
	char		*input_copy;
	int			token_count;

	delimiters = " ";
	input_copy = ft_strdup(data->user_input);
	if (!input_copy)
		return (NULL);
	token_count = count_tokens(input_copy, delimiters);
	free(input_copy);
	input_copy = ft_strdup(data->user_input);
	if (!input_copy)
		return (NULL);
	data->tokens = extract_tokens(input_copy, delimiters, token_count, env);
	free(input_copy);
	return (data->tokens);
}
