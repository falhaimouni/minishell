/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_udigit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshawish <sshawish@student.42amman.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:46:03 by sshawish          #+#    #+#             */
/*   Updated: 2024/09/11 14:46:11 by sshawish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_print_udigit(unsigned long n, int base, int uppercase)
{
	int		count;
	char	*symbols;

	count = 0;
	if (base == 16 && uppercase)
		symbols = "0123456789ABCDEF";
	else
		symbols = "0123456789abcdef";
	if (n < (unsigned long)base)
	{
		return (ft_print_char(symbols[n]));
	}
	else
	{
		count = ft_print_udigit(n / base, base, uppercase);
		return (count + ft_print_udigit(n % base, base, uppercase));
	}
}
