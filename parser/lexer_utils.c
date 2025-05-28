/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshawish <sshawish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:44:07 by sshawish          #+#    #+#             */
/*   Updated: 2025/02/24 10:51:53 by sshawish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*last_pos;
	char		*token_start;

	if (str == NULL)
		str = last_pos;
	if (str == NULL)
		return (NULL);
	while (*str && ft_strchr(delim, *str))
		str++;
	if (*str == '\0')
		return (NULL);
	token_start = str;
	while (*str && !ft_strchr(delim, *str))
		str++;
	if (*str != '\0')
	{
		*str = '\0';
		last_pos = str + 1;
	}
	else
		last_pos = NULL;
	return (token_start);
}

int	count_tokens(char *input, const char *delimiters)
{
	char	*token;
	int		count;

	count = 0;
	token = ft_strtok(input, delimiters);
	while (token != NULL)
	{
		count++;
		token = ft_strtok(NULL, delimiters);
	}
	return (count);
}

bool	is_delimiter(char c, const char *delim)
{
	return (c && ft_strchr(delim, c));
}

bool	closed_quotes(const char *input)
{
	bool	in_quotes;
	char	quote_char;

	in_quotes = false;
	quote_char = '\0';
	while (*input)
	{
		if ((*input == '\"' || *input == '\'') && (!in_quotes
				|| *input == quote_char))
		{
			if (in_quotes)
			{
				in_quotes = false;
				quote_char = '\0';
			}
			else
			{
				in_quotes = true;
				quote_char = *input;
			}
		}
		input++;
	}
	return (!in_quotes);
}
