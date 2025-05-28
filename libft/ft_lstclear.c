/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falhaimo <falhaimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 20:26:34 by sshawish          #+#    #+#             */
/*   Updated: 2025/03/08 10:35:42 by falhaimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
//frees every successor of the node
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;
	t_list	*next_node;

	if (!*lst || !del)
		return ;
	current = *lst;
	while (current)
	{
		next_node = current->next;
		ft_lstdelone(current, del);
		current = next_node;
	}
	*lst = NULL;
}
