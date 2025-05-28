/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshawish <sshawish@student.42amman.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 14:42:17 by sshawish          #+#    #+#             */
/*   Updated: 2024/09/01 15:42:15 by sshawish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
//size_t  strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	src_len;
	size_t	dst_len;

	j = 0;
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	i = dst_len;
	if (!dst || !src)
		return (0);
	if (size <= dst_len)
		return (size + src_len);
	while (src[j] != '\0' && (i + 1) < size)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (src_len + dst_len);
}
/*
#include<stdio.h>
#include<string.h>

int	main()
{
	char	dst[] = "hello";
	char	src[] = "world";
	printf("my fun :%zu\n", ft_strlcat(dst, src, 6));
	printf("original fun :%zu\n", strlcat(dst, src, 20));
}
*/
