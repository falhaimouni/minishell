/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshawish <sshawish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:57:58 by sshawish          #+#    #+#             */
/*   Updated: 2025/04/09 10:05:00 by sshawish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
//Copies a block of memory
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (!d && !s)
		return (NULL);
	while (n > 0)
	{
		*d = *s;
		d++;
		s++;
		n--;
	}
	return (dest);
}
/*
#include<stdio.h>
#include<string.h>
int main() {
    char src[] = "Hello, World!";
    char dest[] = "this is memcpy";

    ft_memcpy(dest, src, 9);
    printf("my fun = %s\n", dest);

    memcpy(dest, src, 9);
    printf("original fun = %s\n", dest);

    return 0;
}
*/
