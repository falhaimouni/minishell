/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshawish <sshawish@student.42amman.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:19:06 by sshawish          #+#    #+#             */
/*   Updated: 2024/09/11 15:29:37 by sshawish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_format(char specifier, va_list ap)
{
	int	count;

	count = 0;
	if (specifier == 'c')
		count += ft_print_char(va_arg(ap, int));
	else if (specifier == 's')
		count += ft_print_str(va_arg(ap, char *));
	else if (specifier == 'p')
		count += ft_print_address(va_arg(ap, void *));
	else if (specifier == 'd' || specifier == 'i')
		count += ft_print_sdigit((long)(va_arg(ap, int)), 10, 0);
	else if (specifier == 'u')
		count += ft_print_udigit((long)(va_arg(ap, unsigned int)), 10, 0);
	else if (specifier == 'x')
		count += ft_print_udigit((long)(va_arg(ap, unsigned int)), 16, 0);
	else if (specifier == 'X')
		count += ft_print_udigit((long)(va_arg(ap, unsigned int)), 16, 1);
	else if (specifier == '%')
		count += ft_print_char('%');
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int		count;
	va_list	ap;

	count = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
			count += ft_print_format(*(++format), ap);
		else
			count += write(1, format, 1);
		++format;
	}
	va_end(ap);
	return (count);
}
/*
#include <stdio.h>
#include <limits.h>
int main() 
{
    int ft_printf_result = ft_printf("%s\n", "hello");
    int printf_result = printf("%s\n", "hello");
    printf("%d\n", ft_printf_result);
    printf("%d\n", printf_result);

    ft_printf_result = ft_printf("%d\n", 42);
    printf_result = printf("%d\n", 42);
    printf("%d\n", ft_printf_result);
    printf("%d\n", printf_result);

    ft_printf_result = ft_printf("%i\n", 42);
    printf_result = printf("%i\n", 42);
    printf("%d\n", ft_printf_result);
    printf("%d\n", printf_result);

    ft_printf_result = ft_printf("%c\n", 'g');
    printf_result = printf("%c\n", 'g');
    printf("%d\n", ft_printf_result);
    printf("%d\n", printf_result);


    ft_printf_result = ft_printf("%x\n", 25516);
    printf_result = printf("%x\n", 25516);
    printf("%d\n", ft_printf_result);
    printf("%d\n", printf_result);

    ft_printf_result = ft_printf("%X\n", 25516);
    printf_result = printf("%X\n", 25516);
    printf("%d\n", ft_printf_result);
    printf("%d\n", printf_result);

    ft_printf_result = ft_printf("%%\n");
    printf_result = printf("%%\n");
    printf("%d\n", ft_printf_result);
    printf("%d\n", printf_result);

    void *ptr = (void *)4242;
    ft_printf_result = ft_printf("%p\n", ptr);
    printf_result = printf("%p\n", ptr);
    printf("%d\n", ft_printf_result);
    printf("%d\n", printf_result);

    ft_printf_result = ft_printf("%u\n", 4294967295U);
    printf_result = printf("%u\n", 4294967295U);
    printf("%d\n", ft_printf_result);
    printf("%d\n", printf_result);

    return 0;
}
*/
