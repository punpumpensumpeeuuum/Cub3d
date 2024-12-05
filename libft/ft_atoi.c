/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:23:03 by jomendes          #+#    #+#             */
/*   Updated: 2023/10/09 12:21:41 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	a;
	int	numb;

	i = 0;
	a = 1;
	numb = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			a = a * (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		numb = (numb * 10) + (str[i] - '0');
		i++;
	}
	return (numb * a);
}
