/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 17:59:47 by aputiev           #+#    #+#             */
/*   Updated: 2023/07/12 20:10:06 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	fd_putchar(int fd, char c)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_ident_process(int fd, char specifier, va_list symbols)
{
	int	char_printed;

	char_printed = 0;
	if (specifier == 'c')
		char_printed += fd_putchar(fd, va_arg(symbols, int));
	if (specifier == '%')
		char_printed += fd_putchar(fd, '%');
	else if (specifier == 'd' || specifier == 'i')
		char_printed += fd_putnbr(fd, va_arg(symbols, int));
	else if (specifier == 's')
		char_printed += fd_putstr(fd, va_arg(symbols, char *));
	else if (specifier == 'u')
		char_printed += fd_put_unsigned_nbr(fd, va_arg(symbols, unsigned int));
	else if (specifier == 'x' || specifier == 'X')
		char_printed += fd_put_hex(fd, va_arg(symbols, int), specifier);
	else if (specifier == 'p')
		char_printed += fd_pointer(fd, va_arg(symbols, unsigned long long));
	return (char_printed);
}

int	ft_printf(int fd, const char *specifier, ...)
{
	int		char_printed;
	int		i;
	va_list	symbols;

	va_start(symbols, specifier);
	i = 0;
	char_printed = 0;
	while (specifier[i])
	{
		if (specifier[i] == '%')
		{
			char_printed += ft_ident_process(fd, specifier[i + 1], symbols);
			i++;
		}
		else
		{
			char_printed += fd_putchar(fd, specifier[i]);
		}
		i++;
	}
	va_end (symbols);
	return (char_printed);
}
