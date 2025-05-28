/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshawish <sshawish@student.42amman.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:45:48 by sshawish          #+#    #+#             */
/*   Updated: 2024/08/29 16:36:27 by sshawish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
//Searches a block of memory for a specific value
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	letter;
	size_t			i;

	str = (unsigned char *)s;
	letter = (unsigned char )c;
	i = 0;
	while (i < n)
	{
		if (str[i] == letter)
			return (&str[i]);
		i++;
	}
	return (0);
}
