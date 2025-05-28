/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_single.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falhaimo <falhaimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:21:24 by sshawish          #+#    #+#             */
/*   Updated: 2025/04/07 15:23:20 by falhaimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	ft_strcpy(result, s1);
	ft_strcat(result, s2);
	free(s1);
	return (result);
}

int	env_arr(t_env *env, char **env_array, int count)
{
	t_env	*temp;
	char	*key_equal;
	int		i;

	temp = env;
	i = 0;
	while (i < count)
	{
		key_equal = ft_strjoin(temp->key, "=");
		if (!key_equal)
			return (free_array(env_array), 0);
		env_array[i] = ft_strjoin(key_equal, temp->value);
		free(key_equal);
		if (!env_array[i])
			return (free_array(env_array), 0);
		temp = temp->next;
		i++;
	}
	env_array[count] = NULL;
	return (1);
}

char	**env_to_char_array(t_env *env)
{
	t_env	*temp;
	char	**env_array;
	int		count;

	temp = env;
	count = 0;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	if (!env_arr(env, env_array, count))
		return (NULL);
	return (env_array);
}

void	execute_with_execve(char *path, char **argv, char **envp)
{
	if (execve(path, argv, envp) == -1)
	{
		perror("Error");
		free(path);
		free(argv);
		free(envp);
		exit(EXIT_FAILURE);
	}
	free(path);
	free(argv);
	free(envp);
}

int	execute_command(t_command **command, t_env *env)
{
	char	**argv;
	char	**envp;
	char	*path;

	if (!command || !(*command) || !(*command)->cmd || !(*command)->args)
		return (1);
	if ((*command)->cmd[0] == '\0')
		return (0);
	if (check_command_path(command, env, &path) == 1)
		return (1);
	prepare_arguments(*command, &argv);
	if (!argv)
	{
		free(path);
		return (1);
	}
	envp = env_to_char_array(env);
	if (!envp)
	{
		free(path);
		free(argv);
		exit(EXIT_FAILURE);
	}
	execute_with_execve(path, argv, envp);
	return (0);
}
