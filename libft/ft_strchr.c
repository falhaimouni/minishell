/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshawish <sshawish@student.42amman.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:50:32 by sshawish          #+#    #+#             */
/*   Updated: 2024/09/01 09:52:26 by sshawish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strchr(const char *s, int c)
{
	char			*str;
	unsigned char	letter;

	str = (char *)s;
	letter = (unsigned char)c;
	while (*str != '\0')
	{
		if (*str == letter)
			return (str);
		str++;
	}
	if (*str == '\0' && letter != '\0')
		return (NULL);
	return (str);
}
/*
#include<stdio.h>
#include<string.h>
int     main()
{
        char    *str = "hello";

	printf("my fun: %s\n", ft_strchr(str, '\0'));

        printf("original fun: %s\n", strchr(str, '\0'));
        return 0;
}
*/
