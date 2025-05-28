/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falhaimo <falhaimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:45:40 by sshawish          #+#    #+#             */
/*   Updated: 2025/04/08 13:39:44 by falhaimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_cmd(t_command command)
{
	char	*home_path;
	int		i;
	bool	newline;

	i = 0;
	if (command.args[0] && ft_strcmp(command.args[0], "~") == 0)
	{
		home_path = getenv("HOME");
		if (home_path)
		{
			printf("%s\n", home_path);
			return ;
		}
	}
	newline = check_newline(command, &i);
	while (command.args[i])
	{
		printf("%s", command.args[i]);
		if (command.args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}

void	cd_cmd(t_command command, int *status)
{
	char	*home_path;

	home_path = getenv("HOME");
	if (!command.args[0] || ft_strcmp(command.args[0], "~") == 0)
	{
		if (home_path && chdir(home_path) != 0)
		{
			perror("cd");
			*status = 1;
		}
		else
			*status = 0;
	}
	else
	{
		if (chdir(command.args[0]) != 0)
		{
			perror("cd");
			*status = 1;
		}
		else
			*status = 0;
	}
}

void	pwd_cmd(t_command command)
{
	char	*buf;

	if (command.args[0])
	{
		ft_putstr_fd("pwd: too many arguments\n", 1);
		return ;
	}
	buf = getcwd(NULL, 0);
	if (buf)
	{
		printf("%s\n", buf);
		free(buf);
	}
	else
		perror("pwd");
}

int	check_cmd(t_command **command, t_shell data, t_env *env)
{
	int	status;

	status = 0;
	if (ft_strcmp(command[0]->cmd, "echo") == 0)
		echo_cmd(**command);
	if (ft_strcmp(command[0]->cmd, "cd") == 0)
		cd_cmd(**command, &status);
	if (ft_strcmp(command[0]->cmd, "pwd") == 0)
		pwd_cmd(**command);
	if (ft_strcmp(command[0]->cmd, "export") == 0)
		export_cmd(*command, &env, &status);
	if (ft_strcmp(command[0]->cmd, "unset") == 0)
		unset_cmd(*command, &env);
	if (ft_strcmp(command[0]->cmd, "env") == 0)
		env_cmd(**command, env, false);
	if (ft_strcmp(command[0]->cmd, "exit") == 0)
	{
		if (exit_cmd(command, data, env) == 1)
			return (1);
	}
	if (env)
		env->exit_status = status;
	return (0);
}
