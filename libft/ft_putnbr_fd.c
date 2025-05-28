/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshawish <sshawish@student.42amman.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:42:11 by sshawish          #+#    #+#             */
/*   Updated: 2024/09/02 16:01:15 by sshawish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == -2147483648)
		write (fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			write(fd, "-", 1);
			n = -n;
			ft_putnbr_fd(n, fd);
		}
		else if (n < 10)
		{
			c = n + '0';
			write (fd, &c, 1);
		}
		else
		{
			ft_putnbr_fd(n / 10, fd);
			c = (n % 10) + '0';
			write (fd, &c, 1);
		}
	}
}
/*
int	main()
{
	ft_putnbr_fd(-321, 1);
	write(1, '\n', 1);
}
*/
