/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falhaimo <falhaimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:20:16 by sshawish          #+#    #+#             */
/*   Updated: 2025/04/08 15:29:45 by falhaimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_user_commands(t_shell *data, t_env *env)
{
	t_command	**commands;
	int			num_commands;

	commands = parse_all_commands(data->tokens, &num_commands);
	if (num_commands > 0)
		execute_commands(commands, *data, env, num_commands);
	cleanup_after_execution(data, commands, num_commands, env);
}

void	handle_signals(t_env *env)
{
	if (g_sig == SIGINT)
	{
		env->exit_status = g_sig + 128;
		g_sig = 0;
	}
}

int	prepare_shell(t_shell *data, t_env *env)
{
	char	*prompt;
	char	*input_prompt;

	set_signal(0);
	env->pwd = getcwd(NULL, 0);
	if (!env->pwd)
	{
		perror("getcwd");
		return (0);
	}
	prompt = ft_strjoin("\U0001F431 \033[38;5;205mCatShell:~\033[0m",
			env->pwd);
	input_prompt = ft_strjoin(prompt, "$ ");
	free(prompt);
	data->user_input = readline(input_prompt);
	free(input_prompt);
	if (!data->user_input)
	{
		printf("Exiting catshell.\n");
		free(env->pwd);
		return (0);
	}
	handle_signals(env);
	return (1);
}

t_env	*new_env_node(char *env)
{
	t_env	*node;
	char	*equal_sign;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	equal_sign = ft_strchr(env, '=');
	if (!equal_sign)
	{
		free(node);
		return (NULL);
	}
	node->key = ft_strndup(env, equal_sign - env);
	node->value = ft_strdup(equal_sign + 1);
	if (!node->key || !node->value)
	{
		free(node->key);
		free(node->value);
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

t_env	*copy_env(char **envp)
{
	t_env	*head;
	t_env	*current;
	t_env	*new_node;
	int		i;

	head = NULL;
	current = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = new_env_node(envp[i]);
		if (!new_node)
			return (free_env_list_on_error(head));
		if (!head)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		i++;
	}
	return (head);
}
