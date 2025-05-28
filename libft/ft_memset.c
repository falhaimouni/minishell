/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshawish <sshawish@student.42amman.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:58:05 by sshawish          #+#    #+#             */
/*   Updated: 2024/08/27 15:05:00 by sshawish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n > 0)
	{
		*ptr = (unsigned char)c;
		ptr++;
		n--;
	}
	return (s);
}

/*
#include <stdio.h>
#include <string.h>
int main()
{
	char str[10] = "HelloWorld";

	printf("Before ft_memset: %s\n", str);

	ft_memset(str, '*', 5);

	printf("After ft_memset: %s\n", str);

	memset(str, '*', 5);

	printf("After ft_memset: %s\n", str);

	return 0;
}
*/
