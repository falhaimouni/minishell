/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshawish <sshawish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 11:28:46 by falhaimo          #+#    #+#             */
/*   Updated: 2025/04/06 14:48:35 by sshawish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_special_var_name(char *start, size_t *i)
{
	char	*var_name;

	if (*start == '$')
	{
		var_name = ft_strdup("$$");
		if (!var_name)
			return (NULL);
		*i += 2;
	}
	else if (*start == '0')
	{
		var_name = ft_strdup("0");
		if (!var_name)
			return (NULL);
		*i += 2;
	}
	else
	{
		var_name = NULL;
	}
	return (var_name);
}

char	*get_numeric_var_name(char *start, size_t *i)
{
	char	*var_name;

	if (ft_isdigit(*start))
	{
		var_name = ft_substr(start, 0, 1);
		*i += 2;
	}
	else
	{
		var_name = NULL;
	}
	return (var_name);
}

char	*get_alnum_var_name(char *start, size_t *i)
{
	char	*var_name;
	size_t	var_len;

	var_len = 0;
	while (start[var_len] && (ft_isalnum(start[var_len])
			|| start[var_len] == '_'))
		var_len++;
	var_name = ft_substr(start, 0, var_len);
	*i += var_len + 1;
	return (var_name);
}

char	*get_var_name(char *start, size_t *i)
{
	char	*var_name;

	var_name = get_special_var_name(start, i);
	if (!var_name)
		var_name = get_numeric_var_name(start, i);
	if (!var_name)
		var_name = get_alnum_var_name(start, i);
	return (var_name);
}

void	heredoc_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = SIGINT;
		close(STDIN_FILENO);
	}
}
