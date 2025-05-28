/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falhaimo <falhaimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:26:59 by sshawish          #+#    #+#             */
/*   Updated: 2025/04/08 23:30:20 by falhaimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_consecutive_redirections(char *input, int i, t_env *env)
{
	if ((input[i] == '>' && input[i + 1] == '>' && input[i + 2] == '>')
		|| (input[i] == '<' && input[i + 1] == '<' && input[i + 2] == '<'))
	{
		if (input[i] == '>')
			print_syntax_error(">", env);
		else
			print_syntax_error("<", env);
		return (1);
	}
	return (0);
}

int	check_redirection_syntax(char *input, t_env *env)
{
	int	i;
	int	j;

	i = 0;
	while (input[i])
	{
		if (input[i] == '<' || input[i] == '>')
		{
			j = i;
			while (input[j] == '<' || input[j] == '>')
				j++;
			while (input[j] == ' ' || input[j] == '\t')
				j++;
			if (input[j] == '\0' || input[j] == '\n')
			{
				if (input[i] == '<')
					print_syntax_error("<", env);
				else
					print_syntax_error(">", env);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	check_last_pipe(t_env *env)
{
	ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
	env->exit_status = 2;
	return (1);
}

int	pipe_error(char c, int *in_single_quote,
	int *in_double_quote, int *last_was_pipe)
{
	if (c == '\'' && !(*in_double_quote))
		*in_single_quote = !(*in_single_quote);
	if (c == '"' && !(*in_single_quote))
		*in_double_quote = !(*in_double_quote);
	if (*in_single_quote || *in_double_quote)
		return (1);
	if (c == '|')
	{
		if (*last_was_pipe)
			return (-1);
		*last_was_pipe = 1;
	}
	else if (c != ' ')
		*last_was_pipe = 0;
	return (0);
}

int	check_pipe_syntax(char *input, t_env *env)
{
	int	i;
	int	last_pipe;
	int	in_squote;
	int	in_dquote;
	int	result;

	i = 0;
	last_pipe = 1;
	in_squote = 0;
	in_dquote = 0;
	while (input[i])
	{
		result = pipe_error(input[i], &in_squote, &in_dquote, &last_pipe);
		if (result == 1)
		{
			i++;
			continue ;
		}
		if (result == -1)
			return (check_last_pipe(env));
		i++;
	}
	if (!in_squote && !in_dquote && last_pipe)
		return (check_last_pipe(env));
	return (0);
}
