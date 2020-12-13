/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmallado <lmallado@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 00:13:51 by lmallado          #+#    #+#             */
/*   Updated: 2020/05/23 01:04:23 by lmallado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int		n_size(long n, int isminus)
{
	int i;

	i = 0;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	if (isminus == 1)
		i++;
	return (i);
}

static char		*to_char(char *res, int i, long n, int size)
{
	res[i + size] = '\0';
	while (n > 0)
	{
		res[i + size - 1] = n % 10 + '0';
		n /= 10;
		size--;
	}
	return (res);
}

char			*ft_itoa(long n)
{
	char	*res;
	int		i;
	int		isminus;

	i = 0;
	if (n == -2147483648)
		return ("-2147483648");
	if (n == 0)
		return ("0");
	isminus = 0;
	if (n < 0)
	{
		i++;
		isminus = 1;
		n *= -1;
	}
	if (!(res = (char *)malloc((n_size(n, isminus) + 1) * sizeof(char))))
		return (NULL);
	if (isminus == 1)
		res[0] = '-';
	return (to_char(res, i, n, n_size(n, 0)));
}