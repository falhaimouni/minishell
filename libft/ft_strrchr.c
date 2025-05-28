/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshawish <sshawish@student.42amman.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 19:15:55 by sshawish          #+#    #+#             */
/*   Updated: 2024/08/29 19:49:54 by sshawish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	char	letter;
	int		i;

	str = (char *)s;
	letter = (char)c;
	i = ft_strlen(str);
	if (letter == '\0')
		return ((char *)str + i);
	while (i >= 0)
	{
		if (str[i] == letter)
			return ((char *)(str + i));
		i--;
	}
	return (0);
}
/*
#include<stdio.h>
#include<string.h>
int     main()
{
        char    *str = "flower";

	printf("my fun %s\n", ft_strrchr(str, 'f'));

        printf("original fun %s\n", strrchr(str, 'f'));
        return 0;
}
*/
