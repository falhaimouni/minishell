/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_address.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshawish <sshawish@student.42amman.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:22:19 by sshawish          #+#    #+#             */
/*   Updated: 2024/09/11 14:47:10 by sshawish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_print_address(void *ptr)
{
	int				count;
	unsigned long	address;

	count = 0;
	address = (unsigned long) ptr;
	if (address == 0)
		count += ft_print_str("(nil)");
	else
	{
		count += ft_print_str("0x");
		count += ft_print_udigit(address, 16, 0);
	}
	return (count);
}
