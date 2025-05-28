/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshawish <sshawish@student.42amman.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 09:41:51 by sshawish          #+#    #+#             */
/*   Updated: 2024/09/07 18:06:12 by sshawish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*end;
	char	*start;
	char	*strim;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	start = (char *)s1;
	end = (char *)s1 + ft_strlen(s1) - 1;
	while (*start && ft_strchr(set, *start))
		start++;
	while (end >= s1 && ft_strrchr(set, *end))
		end--;
	if (start > end)
		return (ft_strdup(""));
	len = end - start + 1;
	strim = (char *)malloc(sizeof(char) * len + 1);
	if (!strim)
		return (NULL);
	ft_memcpy(strim, start, len);
	strim[len] = '\0';
	return (strim);
}
/*
#include<stdio.h>
int	main(void)
{
	printf("my fun :%s\n", ft_strtrim("hello pip world ", "hi world"));
	return (0);
}
*/
