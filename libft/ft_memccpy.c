/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:13:46 by dsohn             #+#    #+#             */
/*   Updated: 2020/09/29 14:23:08 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	const unsigned char		*s = src;
	unsigned char			*d;

	d = dst;
	while (n-- > 0)
		if ((*d++ = *s++) == (unsigned char)c)
			return (d);
	return (NULL);
}
