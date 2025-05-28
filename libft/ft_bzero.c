/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshawish <sshawish@student.42amman.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:59:49 by sshawish          #+#    #+#             */
/*   Updated: 2024/09/07 15:09:45 by sshawish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}
/*
#include<stdio.h>
#include <string.h>
int	main()
{
	char str[] = "hello world";
	ft_bzero(str, 4);
	printf("ft_bezero is: %s\n", str);
	bzero(str, 4);
        printf("bezero is: %s\n", str);

}
*/
