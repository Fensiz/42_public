/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgreenbl <bgreenbl@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 20:36:23 by bgreenbl          #+#    #+#             */
/*   Updated: 2021/10/04 20:36:26 by bgreenbl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void	ft_nbr_len(int n, int *len)
{
	if (n == -2147483648)
	{
		*len = 11;
		return ;
	}
	else
	{
		if (n < 0)
		{
			(*len)++;
			n = -n;
		}
		if (n > 9)
			ft_nbr_len(n / 10, len);
	}
	(*len)++;
}

static void	ft_putnbr_to_str(int n, char **s)
{
	if (n == -2147483648)
	{
		*(*s)++ = '-';
		ft_putnbr_to_str((n / 10) * (-1), s);
	}
	else
	{
		if (n < 0)
		{
			*(*s)++ = '-';
			n = -n;
		}
		if (n > 9)
			ft_putnbr_to_str(n / 10, s);
	}
	if (n < 0)
		*(*s)++ = -1 * (n % 10) + '0';
	else
		*(*s)++ = n % 10 + '0';
}

char	*ft_itoa(int n)
{
	int		counter;
	char	*str;

	counter = 0;
	ft_nbr_len(n, &counter);
	str = (char *)malloc(counter + 1);
	if (!str)
		exit(1);
	str[counter] = 0;
	ft_putnbr_to_str(n, &str);
	return (str - counter);
}
