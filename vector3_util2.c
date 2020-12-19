/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_util2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 19:14:05 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/19 20:46:42 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"
#include "minirt.h"

t_vector3		vector3_sbtr(t_vector3 v, t_vector3 v2)
{
	return (vector3_init(v.x - v2.x, v.y - v2.y, v.z - v2.z));
}

t_vector3		vector3_random(void)
{
	return (vector3_init(random_double(), random_double(), random_double()));
}

t_vector3		vector3_random_range(double min, double max)
{
	return (vector3_init(random_range(min, max),
		random_range(min, max), random_range(min, max)));
}

t_vector3		vector3_random_unit_sphere(void)
{
	t_vector3 temp;

	temp = vector3_init(0, 0, 0);
	while (1)
	{
		temp = vector3_random_range(-1, 1);
		if (vector3_length_squared(temp) >= 1)
			continue ;
		return (temp);
	}
	return (temp);
}

t_vector3		vector3_norm_random(void)
{
	return (vector3_norm(vector3_random_unit_sphere()));
}
