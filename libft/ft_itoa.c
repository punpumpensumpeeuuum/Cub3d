/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes < jomendes@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:35:52 by jomendes          #+#    #+#             */
/*   Updated: 2023/10/16 16:50:03 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digit_counter(long int n)
{
	int	c;

	c = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		c++;
	}
	return (c);
}

char	*ft_itoa(int n)
{
	int		i;
	int		len;
	char	*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = 0;
	if (n < 0)
		i = 1;
	len = digit_counter(n) + i;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	if (n < 0)
		str[0] = '-';
	str[len] = '\0';
	n = n * (((n < 0) * -2) + 1);
	while (len-- != i)
	{
		str[len] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
