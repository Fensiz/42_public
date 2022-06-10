/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:20:06 by bteak             #+#    #+#             */
/*   Updated: 2021/12/07 18:58:21 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

static const char	*ft_is_sign(const char *str, int *sign)
{
	*sign = 1;
	if (*str == '-')
	{
		*sign = -1;
		++str;
	}
	else
	{
		if (*str == '+')
			++str;
	}
	return (str);
}

t_atoi	ft_atoi(const char *str, t_atoi result)
{
	int				sign;

	str = ft_is_sign(str, &sign);
	while (*str)
	{
		if (*str - '0' > 9 || *str - '0' < 0)
		{
			result.error = 1;
			return (result);
		}
		result.value = (10 * result.value) + *str - '0';
		if (result.value < 0)
		{
			if (result.value == INT_MIN && sign == -1 && !*(str + 1))
				return (result);
			else
			{
				result.error = 1;
				return (result);
			}
		}
		str++;
	}
	result.value = (result.value * sign);
	return (result);
}
