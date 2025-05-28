/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falhaimo <falhaimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:19:51 by sshawish          #+#    #+#             */
/*   Updated: 2025/04/08 13:26:48 by falhaimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*copy_env_sort(t_env *env)
{
	t_env	*new_list;
	t_env	*new_node;
	t_env	*temp;

	new_list = NULL;
	temp = env;
	while (temp)
	{
		new_node = create_env_node(temp);
		if (!new_node)
		{
			free_env_list(new_list);
			return (NULL);
		}
		add_to_list(&new_list, new_node);
		temp = temp->next;
	}
	return (new_list);
}

bool	is_bulit_in(t_command *cmd)
{
	if (!cmd->cmd)
		return (1);
	if (ft_strcmp(cmd->cmd, "echo") == 0
		|| ft_strcmp(cmd->cmd, "cd") == 0
		|| ft_strcmp(cmd->cmd, "pwd") == 0
		|| ft_strcmp(cmd->cmd, "export") == 0
		|| ft_strcmp(cmd->cmd, "unset") == 0
		|| ft_strcmp(cmd->cmd, "env") == 0
		|| ft_strcmp(cmd->cmd, "exit") == 0)
		return (0);
	else
		return (1);
}

void	env_cmd(t_command command, t_env *env, bool is_export)
{
	if (command.args[0])
	{
		printf("env: '%s': No such file or directory\n", command.args[0]);
		return ;
	}
	while (env)
	{
		print_env(env, is_export);
		env = env->next;
	}
}

int	exit_cmd(t_command **command, t_shell data, t_env *env)
{
	int	exit_status;
	int	i;

	(void)data;
	exit_status = 0;
	printf("\U0001F408 exiting catshell \U0001F408\n");
	if (command[0]->args[0])
	{
		i = 0;
		while (command[0]->args[0][i])
		{
			if (!ft_isdigit(command[0]->args[0][i]))
			{
				printf("exit: %s: numeric argument required\n",
					command[0]->args[0]);
				env->exit_status = 2;
				return (1);
			}
			i++;
		}
		exit_status = ft_atoi(command[0]->args[0]);
	}
	env->exit_status = exit_status;
	return (1);
}

void	unset_cmd(t_command *command, t_env **env)
{
	int	i;

	i = 0;
	if (!command->args[i] || !(*env))
		return ;
	while (command->args[i])
	{
		remove_env_variable(command->args[i], env);
		i++;
	}
}
