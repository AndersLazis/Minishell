/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexadecimal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 17:37:43 by aputiev           #+#    #+#             */
/*   Updated: 2023/07/12 20:11:50 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hex_lenght(unsigned int n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		n = (n / 16);
		i++;
	}
	return (i);
}

int	fd_put_hex(int fd, int m, char specifier)
{
	unsigned int	n;

	n = (unsigned int) m;
	if (n == 0)
	{
		return (write(fd, "0", 1));
	}
	else
	{
		if (specifier == 'x')
			fd_hex_lowercase(fd, n);
		if (specifier == 'X')
			fd_hex_uppercase(fd, n);
	}
	return (ft_hex_lenght(n));
}

void	fd_hex_lowercase(int fd, unsigned int n)
{
	if (n > 15)
	{
		fd_hex_lowercase(fd, n / 16);
		fd_hex_lowercase(fd, n % 16);
	}
	else
	{
		if (n <= 9)
			fd_putchar(fd, (n + 48));
		else
			fd_putchar(fd, (n - 10 + 97));
	}
}

void	fd_hex_uppercase(int fd, unsigned int n)
{
	if (n > 15)
	{
		fd_hex_uppercase(fd, n / 16);
		fd_hex_uppercase(fd, n % 16);
	}
	else
	{
		if (n <= 9)
			fd_putchar(fd, (n + 48));
		else
			fd_putchar(fd, n - 10 + 65);
	}
}
