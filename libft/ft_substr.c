/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshawish <sshawish@student.42amman.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 17:41:16 by sshawish          #+#    #+#             */
/*   Updated: 2024/09/01 18:31:34 by sshawish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
//Extracts a part of a string
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;
	char	*p;

	i = start;
	j = 0;
	if (!s)
		return (0);
	str = (char *)s;
	if (ft_strlen(str) <= start)
		return (ft_strdup(""));
	if (ft_strlen(str) - start < len)
		len = ft_strlen(str) - start;
	p = (char *)malloc((len + 1) * sizeof(*s));
	if (!p)
		return (NULL);
	while (i < ft_strlen(str) && j < len)
	{
		p[j] = str[i];
		j++;
		i++;
	}
	p[j] = '\0';
	return (p);
}
/*
#include<stdio.h>
int	main()
{
	char	str[] = "hello world";
	printf("my fun :%s\n", ft_substr(str, 5, 6));
	return (0);
}
*/
