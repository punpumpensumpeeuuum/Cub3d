/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes < jomendes@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:46:40 by jomendes          #+#    #+#             */
/*   Updated: 2023/10/16 15:26:29 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static void print_number(int n, int fd )
// {
//     if ( n > 9)
//        print_number(n / 10, fd);
//     write (fd, &"0123456789"[n % 10] + '0', 1);
// }

static void	print_number(int n, int fd)
{
	if (n <= 9)
		write(fd, &"0123456789"[n % 10], 1);
	else
	{
		print_number(n / 10, fd);
		write(fd, &"0123456789"[n % 10], 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	else
	{
		if (n < 0)
		{
			write(fd, "-", 1);
			n = -n;
		}
		print_number(n, fd);
	}
}
