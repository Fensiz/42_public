/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgreenbl <bgreenbl@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 20:41:26 by bgreenbl          #+#    #+#             */
/*   Updated: 2021/10/04 20:41:28 by bgreenbl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void	ft_free(char **p_arr)
{
	int	i;

	i = 0;
	while (p_arr[i])
	{
		free(p_arr[i++]);
	}
	free(p_arr);
}

static char	*ft_word(char const *p, char c)
{
	int		i;
	char	*res;

	i = 0;
	while (p[i] != c && p[i])
		i++;
	res = (char *)malloc((i + 1) * sizeof(char));
	if (res == NULL)
		exit(1);
	res[i] = 0;
	while (--i >= 0)
		res[i] = p[i];
	return (res);
}

static int	ft_spl_hlp(char **p_arr, char const *str, char c)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (str[++i])
	{
		if (str[i] != c && (i == 0 || str[i - 1] == c))
		{
			p_arr[++j] = ft_word(&str[i], c);
			if (p_arr[j] == NULL)
			{
				ft_free(p_arr);
				return (1);
			}
		}
	}
	p_arr[j + 1] = NULL;
	return (0);
}

void	*ft_split(void *v_str)
{
	int			counter;
	char		**p_arr;
	int			i;
	const char	c = ' ';
	const char	*str = (const char *)v_str;

	if (!str)
		return (NULL);
	i = -1;
	counter = 0;
	while (str[++i])
		if (str[i] != c && (i == 0 || str[i - 1] == c))
			counter++;
	p_arr = (char **)malloc((counter + 1) * sizeof(char *));
	if (p_arr == NULL)
		exit(1);
	i = ft_spl_hlp(p_arr, str, c);
	if (i)
		return (NULL);
	return ((void *)p_arr);
}
