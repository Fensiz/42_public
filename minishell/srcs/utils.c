/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgreenbl <bgreenbl@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 18:48:03 by bgreenbl          #+#    #+#             */
/*   Updated: 2021/12/11 18:48:04 by bgreenbl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	counter;

	counter = 0;
	while (s[counter])
		counter++;
	return (counter);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*new;
	size_t	i;

	len_s1 = 0;
	len_s2 = 0;
	if (s1)
		len_s1 = ft_strlen(s1);
	if (s2)
		len_s2 = ft_strlen(s2);
	new = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!new)
		exit(1);
	new[len_s1 + len_s2] = 0;
	i = 0;
	while (i < len_s1)
		*new++ = s1[i++];
	i = 0;
	while (i < len_s2)
		*new++ = s2[i++];
	return (new - len_s1 - len_s2);
}

int	ft_charjoin(char **s1, char const c)
{
	size_t	len_s1;
	char	*new;
	size_t	i;

	len_s1 = 0;
	if (*s1)
		len_s1 = ft_strlen(*s1);
	if (!c)
		return (0);
	new = (char *)malloc((len_s1 + 2) * sizeof(char));
	if (!new)
		exit(1);
	new[len_s1 + 1] = 0;
	i = 0;
	while (i < len_s1)
		*new++ = (*s1)[i++];
	*new = c;
	free(*s1);
	*s1 = new - len_s1;
	return (0);
}

int	ft_env_size(t_env *lst)
{
	int	counter;

	counter = 0;
	while (lst)
	{
		counter++;
		lst = lst->next;
	}
	return (counter);
}

int	ft_isspace(int c)
{
	return (c == '\t' || c == '\v' || c == '\n' || c == '\r' || c == '\f' \
			|| c == ' ');
}
