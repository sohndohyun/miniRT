/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_util1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 16:13:35 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/04 16:42:58 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"
#include "math.h"

double			vector3_length(t_vector3 v)
{
	return (sqrt(vector3_length_squared(v)));
}

double			vector3_length_squared(t_vector3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

double			vector3_dot(t_vector3 v1, t_vector3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);	
}

t_vector3		vector3_cross(t_vector3 v1, t_vector3 v2)
{
	return (vector3_init(
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
	));
}

t_vector3		vector3_norm(t_vector3 v)
{
	return (vector3_div(v, vector3_length(v)));
}
