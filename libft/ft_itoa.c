/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshawish <sshawish@student.42amman.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:36:30 by sshawish          #+#    #+#             */
/*   Updated: 2024/09/02 14:11:36 by sshawish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	ft_length(long n)
{
	int		i;
	long	len;

	len = n;
	i = 0;
	if (len <= 0)
	{
		len *= -1;
		i++;
	}
	while (len > 0)
	{
		i++;
		len /= 10;
	}
	return (i);
}

static char	ft_negative(long *nb)
{
	*nb *= -1;
	return ('-');
}

char	*ft_itoa(int n)
{
	int		i;
	char	*str;
	long	nb;

	nb = n;
	i = ft_length(n);
	str = (char *)malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	str[i--] = '\0';
	if (nb < 0)
		str[0] = ft_negative(&nb);
	if (nb < 9 || nb == 0)
		str[i--] = nb + '0';
	else
	{
		while (nb > 0)
		{
			str[i--] = (nb % 10) + '0';
			nb /= 10;
		}
	}
	return (str);
}
/*
#include<stdio.h>
int main() 
{
    int n = 7854154;
    printf("The string representation of %s\n", ft_itoa(n));
    return 0;
}
*/
