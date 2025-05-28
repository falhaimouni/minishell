/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshawish <sshawish@student.42amman.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 22:25:18 by sshawish          #+#    #+#             */
/*   Updated: 2024/09/01 11:43:15 by sshawish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
//search little in big
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*slong;
	size_t	i;
	size_t	j;
	size_t	l_len;

	i = 0;
	slong = (char *)big;
	l_len = ft_strlen(little);
	if (l_len == 0 || slong == little)
		return (slong);
	while (slong[i] != '\0' && i < len)
	{
		j = 0;
		while (slong[i + j] != '\0' && little[j] != '\0'
			&& slong[i + j] == little[j] && i + j < len)
			j++;
		if (j == l_len)
			return (slong + i);
		i++;
	}
	return (0);
}
/*
#include<stdio.h>
#include <string.h>

int main()
{
    char str1[] = "foo bar baz";
    char str2[] = "baz";
    printf("my fun : %s\n", ft_strnstr(str1, str2, 8));
    return 0;
}
*/
