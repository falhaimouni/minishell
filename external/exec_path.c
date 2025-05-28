/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshawish <sshawish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 23:36:19 by falhaimo          #+#    #+#             */
/*   Updated: 2025/04/06 15:54:29 by sshawish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

char	**get_full_path(t_env *env)
{
	while (env && ft_strcmp(env->key, "PATH") != 0)
		env = env->next;
	if (!env || !env->value)
		return (NULL);
	return (ft_split(env->value, ':'));
}

char	*find_path(t_command *cmd, t_env *env)
{
	char	**full_path;
	char	*path;
	char	*part_path;
	int		i;

	full_path = get_full_path(env);
	if (!full_path)
		return (NULL);
	i = 0;
	while (full_path[i])
	{
		part_path = ft_strjoin(full_path[i], "/");
		path = ft_strjoin(part_path, cmd->cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
		{
			free_array(full_path);
			return (path);
		}
		free(path);
		i++;
	}
	free_array(full_path);
	return (NULL);
}

int	check_path(t_command **command, t_env *env, char **path)
{
	*path = ft_strdup((*command)->cmd);
	if (!*path)
		return (0);
	if (is_directory(*path))
	{
		printf("%s: is a directory\n", *path);
		free(*path);
		env->exit_status = 126;
		return (1);
	}
	if (access(*path, F_OK) != 0)
	{
		free(*path);
		perror((*command)->cmd);
		env->exit_status = 127;
		return (1);
	}
	if (access(*path, X_OK) != 0)
	{
		free(*path);
		perror((*command)->cmd);
		env->exit_status = 126;
		return (1);
	}
	return (0);
}

int	check_command_path(t_command **command, t_env *env, char **path)
{
	if ((*command)->cmd[0] == '/' || (*command)->cmd[0] == '.')
	{
		if (check_path(command, env, path))
			return (1);
	}
	else
	{
		*path = find_path(*command, env);
		if (!*path)
		{
			write(2, (*command)->cmd, ft_strlen((*command)->cmd));
			write(2, ": command not found\n", 20);
			env->exit_status = 127;
			return (1);
		}
	}
	return (0);
}
