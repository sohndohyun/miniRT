/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 16:09:46 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/04 16:15:31 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"

t_vector3		vector3_init(double x, double y, double z)
{
	t_vector3 temp;

	temp.x = x;
	temp.y = y;
	temp.z = z;
	return (temp);
}

t_vector3		vector3_not(t_vector3 v)
{
	return (vector3_init(-v.x, -v.y, -v.z));
}

t_vector3		vector3_add(t_vector3 v1, t_vector3 v2)
{
	return (vector3_init(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

t_vector3		vector3_mult(t_vector3 v, double d)
{
	return (vector3_init(v.x * d, v.y * d, v.z * d));
}

t_vector3		vector3_div(t_vector3 v, double d)
{
	return (vector3_mult(v, 1 / d));
}
