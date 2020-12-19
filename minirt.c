/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 00:22:02 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/19 17:09:11 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	random_double(void)
{
	return ((double)ft_rand() / (RAND_MAX + 1.0));
}

double	random_range(double min, double max)
{
	return (min + (max - min) * random_double());
}

double	dtor(double d)
{
	return (d * PI / 180.0);
}

double	clamp(double x, double min, double max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}
