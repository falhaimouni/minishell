/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshawish <sshawish@student.42amman.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:07:57 by sshawish          #+#    #+#             */
/*   Updated: 2024/09/11 12:15:26 by sshawish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_print_str(char *str)
{
	int	count;

	count = 0;
	if (str == NULL)
		return (ft_print_str("(null)"));
	while (*str)
	{
		count += ft_print_char((int) *(str++));
	}
	return (count);
}
