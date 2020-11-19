/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_util3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 02:15:06 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/18 21:10:46 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"
#include <math.h>

t_vector3		vector3_random_hemisphere(t_vector3 norm)
{
	t_vector3 temp;

	temp = vector3_random_unit_sphere();
	if (vector3_dot(temp, norm) > 0.0)
		return (temp);
	return (vector3_not(temp));
}

int				vector3_near_zero(t_vector3 vec3)
{
	const double s = 1e-8;

	return (fabs(vec3.x) < s && fabs(vec3.y) < s && fabs(vec3.y) < s);
}

t_vector3		vector3_reflect(t_vector3 v, t_vector3 n)
{
	return (vector3_sbtr(v, vector3_mult(n, vector3_dot(v, n) * 2)));
}

t_vector3		vector3_mult_vec(t_vector3 v1, t_vector3 v2)
{
	return vector3_init(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

t_vector3		vector3_refract(t_vector3 uv, t_vector3 n, double etai_over_etat)
{
	double cos_theta;
	t_vector3 out_perp;
	t_vector3 out_parallel;

	cos_theta = fmin(vector3_dot(vector3_not(uv), n), 1.0);
	out_perp = vector3_mult(vector3_add(uv, vector3_mult(n, cos_theta)), etai_over_etat);
	out_parallel = vector3_mult(n, -sqrt(fabs(1.0 - vector3_length_squared(out_perp))));
	return (vector3_add(out_perp, out_parallel));
}
