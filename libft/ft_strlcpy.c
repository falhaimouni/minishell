/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshawish <sshawish@student.42amman.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:00:20 by sshawish          #+#    #+#             */
/*   Updated: 2024/09/01 15:42:58 by sshawish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
//size_t  strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen(src);
	if (!dst || !src)
		return (src_len);
	if (!size)
		return (src_len);
	while (i < size - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	if (size > 0)
		dst[i] = '\0';
	return (src_len);
}
/*
#include<stdio.h>
#include<string.h>
int     main()
{
        char    dst[] = "hello";
        char    src[] = "world";
        printf("my fun:%zu\n", ft_strlcpy(dst, src, 10));
        printf("original fun:%zu\n", strlcpy);
        return (0);
}
*/
