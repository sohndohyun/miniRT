/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 20:39:06 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/28 18:21:09 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "plane.h"

static void		plane_get_uv(t_vector3 p, t_vector3 o, double *u, double *v)
{
	double xx;
	double zz;

	xx = o.x - p.x;
	zz = o.z - p.z;
	*u = (fabs(o.x - p.x));
	*v = (fabs(o.z - p.z));
}

t_result		plane_hit(void *obj, t_ray r, double t_min, double t_max)
{
	t_plane *plane;
	t_result result;
	double denom;

	result.ret = 0;
	plane = obj;
	if ((denom = vector3_dot(plane->face, r.dir)) == 0)
		return (result);
	result.t = vector3_dot(vector3_sbtr(plane->orig, r.orig), vector3_norm(plane->face)) / denom;
	if (result.t < t_min || t_max < result.t)
		return (result);
	result.p = ray_at(r, result.t);
	result_set_face_normal(&result, r, plane->face);
	plane_get_uv(result.p, plane->orig, &result.u, &result.v);
	result.mat = plane->mat;
	result.ret = 1;
	return (result);	
}

t_hittable		*plane_alloc(t_vector3 orig, t_vector3 face, t_material *mat)
{
	t_plane *plane;
	t_hittable *hit;

	plane = malloc(sizeof(t_plane));
	plane->face = face;
	plane->orig = orig;
	plane->mat = mat;
	hit = malloc(sizeof(t_hittable));
	hit->hit = plane_hit;
	hit->object = plane;
	hit->del = plane_free;
	return (hit);
}

void			plane_free(void *plane)
{
	t_plane *temp;

	temp = plane;
	temp->mat->del(temp->mat->obj);
	free(temp->mat);
	free(temp);
}

