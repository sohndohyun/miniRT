/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 23:52:03 by dsohn             #+#    #+#             */
/*   Updated: 2020/09/30 04:14:03 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_nbrlen(int n)
{
	int len;

	len = 0;
	if (n < 0)
	{
		len = 1;
		n = -n;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	int		len;
	int		temp;
	char	*result;

	if (n == -2147483648 || n == 0)
		return (ft_strdup(n == 0 ? "0" : "-2147483648"));
	temp = n;
	len = ft_nbrlen(n);
	if (!(result = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	result[len] = 0;
	if (n < 0)
	{
		result[0] = '-';
		n = -n;
	}
	while (n != 0)
	{
		result[--len] = n % 10 + '0';
		n /= 10;
	}
	return (result);
}
