/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falhaimo <falhaimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:59:29 by falhaimo          #+#    #+#             */
/*   Updated: 2025/04/08 23:26:17 by falhaimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig = 0;

void	print_syntax_error(char *unexpected, t_env *env)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(unexpected, 2);
	ft_putstr_fd("'\n", 2);
	env->exit_status = 2;
}

t_env	*initialize_environment(char **envp)
{
	t_env	*env;

	env = copy_env(envp);
	env->exit_status = 0;
	env->redir_flag = 0;
	g_sig = 0;
	return (env);
}

int	process_user_input(t_shell *data, t_env *env)
{
	data->tokens = lexing(data, env);
	if (data->tokens == NULL)
	{
		cleanup_after_null_tokens(data, env);
		return (0);
	}
	return (1);
}

void	main_loop(t_shell *data, t_env *env)
{
	while (1)
	{
		if (!prepare_shell(data, env))
			break ;
		if (!process_user_input(data, env))
			continue ;
		execute_user_commands(data, env);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		data;
	t_env		*env;

	(void)argc;
	(void)argv;
	env = initialize_environment(envp);
	main_loop(&data, env);
	free_env_list(env);
	return (0);
}
