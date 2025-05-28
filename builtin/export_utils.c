/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falhaimo <falhaimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:06:45 by falhaimo          #+#    #+#             */
/*   Updated: 2025/03/10 11:01:03 by falhaimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_env_node(t_env *node, char *value)
{
	free(node->value);
	node->value = ft_strdup(value);
	if (!node->value)
		return ;
}

void	add_env_node(t_env **env, char *key, char *value)
{
	t_env	*new_node;
	t_env	*last;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->key = ft_strdup(key);
	if (!new_node->key)
		return ;
	new_node->value = ft_strdup(value);
	if (!new_node->value)
		return ;
	new_node->next = NULL;
	if (*env == NULL)
		*env = new_node;
	else
	{
		last = *env;
		while (last->next)
		{
			last = last->next;
		}
		last->next = new_node;
	}
}

void	update_or_add_env_node(char *key, char *value, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			update_env_node(tmp, value);
			return ;
		}
		tmp = tmp->next;
	}
	add_env_node(env, key, value);
}

t_env	*lstlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_to_list(t_env **head, t_env *new_node)
{
	t_env	*last_node;

	if (*head)
	{
		last_node = lstlast(*head);
		last_node->next = new_node;
	}
	else
		*head = new_node;
}
