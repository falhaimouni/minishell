/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshawish <sshawish@student.42amman.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:34:54 by sshawish          #+#    #+#             */
/*   Updated: 2024/09/01 17:02:40 by sshawish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
//copies the contents of the original string
char	*ft_strdup(const char *s)
{
	char	*str1;
	char	*str2;
	int		i;

	str1 = (char *)s;
	i = ft_strlen(str1);
	str2 = (char *)malloc((i + 1) * sizeof(char));
	if (!str2)
		return (NULL);
	i = 0;
	while (str1[i] != '\0')
	{
		str2[i] = str1[i];
		i++;
	}
	str2[i] = '\0';
	return (str2);
}
/*
#include<stdio.h>
#include<string.h>
int	main()
{
	char	str[] = "Hello everyone";
	printf("my fun: %s\n", ft_strdup(str));
	printf("original fun: %s\n", strdup(str));
}
*/
