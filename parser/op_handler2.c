/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_handler2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falhaimo <falhaimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:56:47 by falhaimo          #+#    #+#             */
/*   Updated: 2025/04/08 12:56:49 by falhaimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_op(t_lex *lex)
{
	if (*lex->ptr == '|')
		handle_pipe(lex);
	else if (*lex->ptr == '>' && *(lex->ptr + 1) != '>')
		handle_outred(lex);
	else if (*lex->ptr == '>' && *(lex->ptr + 1) == '>')
		handle_outapp(lex);
	else if (*lex->ptr == '<' && *(lex->ptr + 1) != '<')
		handle_inputred(lex);
	else if (*lex->ptr == '<' && *(lex->ptr + 1) == '<')
	{
		handle_heredoc(lex);
		lex->in_heredoc = 1;
	}
	else
		lex->in_heredoc = 0;
}

bool	check_op(t_lex *lex)
{
	return (*lex->ptr == '|' || *lex->ptr == '<'
		|| *lex->ptr == '>' || (*lex->ptr == '<' && *(lex->ptr + 1) == '<')
		|| (*lex->ptr == '>' && *(lex->ptr + 1) == '>'));
}
