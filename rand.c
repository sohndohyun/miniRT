/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 04:20:29 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/19 17:11:39 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "stdlib.h"

unsigned int g_next = 1;

void	ft_srand(unsigned int seed)
{
	g_next = seed;
}

int		ft_rand(void)
{
	return ((g_next = g_next * 1103515245 + 12345)
		% ((unsigned int)RAND_MAX + 1));
}
