/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 17:44:15 by aputiev           #+#    #+#             */
/*   Updated: 2023/07/12 20:11:28 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_ptr_lenght(unsigned long long n)
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

void	ft_hex_ptr(int fd, unsigned long long n)
{
	if (n > 15)
	{
		ft_hex_ptr(fd, n / 16);
		ft_hex_ptr(fd, n % 16);
	}
	else
	{
		if (n <= 9)
			fd_putchar(fd, (n + 48));
		else
			fd_putchar(fd, n - 10 + 97);
	}
}

int	fd_pointer(int fd, unsigned long long n)
{
	if (n == 0)
	{
		return (write(fd, "0x0", 3));
	}
	else
	{
		write(fd, "0x", 2);
		ft_hex_ptr(fd, n);
	}
	return (ft_ptr_lenght(n)+2);
}
