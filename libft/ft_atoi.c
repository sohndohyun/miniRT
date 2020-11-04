/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 16:22:24 by dsohn             #+#    #+#             */
/*   Updated: 2020/09/30 17:32:23 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	unsigned int	res;
	unsigned int	chk;
	int				neg;

	res = 0;
	chk = 214748364;
	while (*str == ' ' || *str == '\n' || *str == '\t' ||
			*str == '\v' || *str == '\f' || *str == '\r')
		++str;
	if (*str == '-')
		neg = -1;
	neg = *str == '-' ? -1 : 1;
	if (*str == '-' || *str == '+')
		++str;
	while (ft_isdigit(*str))
	{
		if ((res > chk || (res == chk && *str > '7')) && neg > 0)
			return (-1);
		if ((res > chk || (res == chk && *str > '8')) && neg < 0)
			return (0);
		res = res * 10 + (*str++ - '0');
	}
	return (res * neg);
}
