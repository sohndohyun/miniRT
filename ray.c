/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 17:24:22 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/19 17:11:59 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_ray			ray_init(t_vector3 orig, t_vector3 dir)
{
	t_ray temp;

	temp.dir = vector3_norm(dir);
	temp.orig = orig;
	return (temp);
}

t_vector3		ray_at(t_ray ray, double t)
{
	return (vector3_add(ray.orig, vector3_mult(ray.dir, t)));
}

int				ray_plane_t(t_ray ray, t_ray plane, double *t)
{
	double denom;

	if ((denom = vector3_dot(plane.dir, ray.dir)) == 0)
		return (0);
	*t = vector3_dot(vector3_sbtr(plane.orig, ray.orig),
		vector3_norm(plane.dir)) / denom;
	return (1);
}
