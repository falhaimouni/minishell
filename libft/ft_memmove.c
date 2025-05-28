/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshawish <sshawish@student.42amman.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:20:38 by sshawish          #+#    #+#             */
/*   Updated: 2024/08/27 15:00:50 by sshawish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
//Copies a block of memory and handles overlapping
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (!d && !s)
		return (NULL);
	if (s < d)
	{
		while (n > 0)
		{
			d[n - 1] = s[n - 1];
			n--;
		}
		return (dest);
	}
	else
	{
		while (n > 0)
		{
			*d++ = *s++;
			n--;
		}
		return (dest);
	}
}
/*
#include <stdio.h>
#include <string.h>

int main()
{
    char src[] = "hello Wrold!";
    char dest[]="fatoom jkjkjkjk";

    ft_memmove(dest, src, 7);
    printf("Copied dest: %s\n", dest);

    memmove(dest, src, 7);
    printf("Copied dest: %s\n", dest);

    return 0;
}
*/
