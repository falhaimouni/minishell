/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_handler1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falhaimo <falhaimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:02:19 by falhaimo          #+#    #+#             */
/*   Updated: 2025/02/04 15:17:33 by falhaimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_pipe(t_lex *lex)
{
	if (lex->current_token)
	{
		lex->tokens[lex->i++] = lex->current_token;
		lex->current_token = NULL;
	}
	lex->tokens[lex->i++] = ft_strdup("|");
	if (!lex->tokens[lex->i - 1])
		return ;
}

void	handle_outred(t_lex *lex)
{
	if (lex->current_token)
	{
		lex->tokens[lex->i++] = lex->current_token;
		lex->current_token = NULL;
	}
	lex->tokens[lex->i++] = ft_strdup(">");
	if (!lex->tokens[lex->i - 1])
		return ;
}

void	handle_outapp(t_lex *lex)
{
	if (lex->current_token)
	{
		lex->tokens[lex->i++] = lex->current_token;
		lex->current_token = NULL;
	}
	lex->tokens[lex->i++] = ft_strdup(">>");
	if (!lex->tokens[lex->i - 1])
		return ;
	lex->ptr++;
}

void	handle_inputred(t_lex *lex)
{
	if (lex->current_token)
	{
		lex->tokens[lex->i++] = lex->current_token;
		lex->current_token = NULL;
	}
	lex->tokens[lex->i++] = ft_strdup("<");
	if (!lex->tokens[lex->i - 1])
		return ;
}

void	handle_heredoc(t_lex *lex)
{
	if (lex->current_token)
	{
		lex->tokens[lex->i++] = lex->current_token;
		lex->current_token = NULL;
	}
	lex->tokens[lex->i++] = ft_strdup("<<");
	if (!lex->tokens[lex->i - 1])
		return ;
	lex->ptr++;
}
