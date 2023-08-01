/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numbers_strings.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 17:30:25 by aputiev           #+#    #+#             */
/*   Updated: 2023/07/12 20:11:58 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	fd_putstr(int fd, char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		write(fd, "(null)", 6);
		return (6);
	}
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	return (i);
}

int	ft_num_uns_lenght(unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

int	ft_num_lenght(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		i = 1;
		n = -n;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

int	fd_putnbr(int fd, int n)
{
	if (n == -2147483648)
	{
		fd_putstr(fd, "-2147483648");
	}
	else if (n < 0)
	{
		fd_putchar(fd, '-');
		fd_putnbr(fd, -n);
	}
	else if (n > 9)
	{
		fd_putnbr(fd, n / 10);
		fd_putnbr(fd, n % 10);
	}
	else
	{
		fd_putchar(fd, n + 48);
	}
	return (ft_num_lenght(n));
}

int	fd_put_unsigned_nbr(int fd, unsigned int n)
{
	int	len;

	len = ft_num_uns_lenght(n);
	if (n > 9)
	{
		fd_putnbr(fd, n / 10);
		fd_putnbr(fd, n % 10);
	}
	else
	{
		fd_putchar(fd, (n + 48));
	}
	return (len);
}
