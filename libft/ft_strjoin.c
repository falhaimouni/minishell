/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshawish <sshawish@student.42amman.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 08:43:08 by sshawish          #+#    #+#             */
/*   Updated: 2024/09/02 09:37:18 by sshawish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int			i;
	int			j;
	char		*str1;
	char		*str2;
	char		*p;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	str1 = (char *)s1;
	str2 = (char *)s2;
	p = (char *)malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	if (!p)
		return (NULL);
	while (str1[i] != '\0')
		p[j++] = str1[i++];
	i = 0;
	while (str2[i] != '\0')
		p[j++] = str2[i++];
	p[j] = '\0';
	return (p);
}
/*
#include<stdio.h>
int	main()
{
	printf("my fun : %s\n", ft_strjoin("this is ", "strjoin"));
	return (0);
}
*/
