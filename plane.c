/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 20:39:06 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/26 21:34:34 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "plane.h"

t_result		plane_hit(void *obj, t_ray r, double t_min, double t_max)
{
	t_plane *plane;
	t_result res;
	t_vector3 on;
	double denom;

	res.ret = 0;
	plane = obj;
	if ((denom = vector3_dot(plane->face, r.dir)) <= 1e-6)
		return (res);
	res.t = vector3_dot(vector3_sbtr(plane->orig, r.orig), r.dir) / denom;
	if (res.t < t_min || t_max < res.t)
		return (res);
	res.p = ray_at(r, res.t);
	res.mat = plane->mat;
	res.ret = 1;
	result_set_face_normal(&res, r, plane->face);
	
	return (res);	
}

t_hittable		*plane_alloc(t_vector3 orig, t_vector3 face, t_material *mat)
{

}

void			plane_free(void *sphere)
{
	
}

