/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 18:08:21 by aputiev           #+#    #+#             */
/*   Updated: 2023/07/12 20:12:07 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

int		ft_hex_lenght(unsigned int n);
int		fd_put_hex(int fd, int m, char specifier);
void	fd_hex_lowercase(int fd, unsigned int n);
void	fd_hex_uppercase(int fd, unsigned int n);
int		fd_putstr(int fd, char *s);
int		ft_num_uns_lenght(unsigned int n);
int		ft_num_lenght(int n);
int		fd_putnbr(int fd, int n);
int		fd_put_unsigned_nbr(int fd, unsigned int n);
int		ft_ptr_lenght(unsigned long long n);
void	ft_hex_ptr(int fd, unsigned long long n);
int		fd_pointer(int fd, unsigned long long n);
int		fd_putchar(int fd, char c);
int		ft_ident_process(int fd, char specifier, va_list symbols);
int		ft_printf(int fd, const char *specifier, ...);
#endif
