/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 20:39:06 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/19 17:10:52 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "plane.h"
#include <stdio.h>

static void		plane_get_uv(
		t_vector3 p, t_vector3 n, double *u, double *v)
{
	t_vector3	uv;
	t_vector3	vv;
	int			a;

	uv = compute_primary_dir(n);
	vv = vector3_cross(n, uv);
	*u = vector3_dot(uv, p);
	*v = vector3_dot(vv, p);
	a = *u;
	*u -= a;
	a = *v;
	*v -= a;
	*u = *u < 0 ? 1.0 + *u : *u;
	*v = *v < 0 ? 1.0 + *v : *v;
}

t_result		plane_hit(void *obj, t_ray r, double t_min, double t_max)
{
	t_plane		*plane;
	t_result	result;

	result.ret = 0;
	plane = obj;
	if (!ray_plane_t(r, ray_init(plane->orig, plane->face), &result.t))
		return (result);
	if (result.t < t_min || t_max < result.t)
		return (result);
	result.p = ray_at(r, result.t);
	result_set_face_normal(&result, r, plane->face);
	plane_get_uv(vector3_sbtr(
		plane->orig, result.p), plane->face, &result.u, &result.v);
	result.mat = plane->mat;
	result.ret = 1;
	return (result);
}

t_hittable		*plane_alloc(t_vector3 orig, t_vector3 face, t_material *mat)
{
	t_plane		*plane;
	t_hittable	*hit;

	plane = (t_plane*)malloc(sizeof(t_plane));
	plane->face = face;
	plane->orig = orig;
	plane->mat = mat;
	hit = (t_hittable*)malloc(sizeof(t_hittable));
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
