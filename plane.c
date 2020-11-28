/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 20:39:06 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/28 21:38:49 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "plane.h"

static t_vector3 compute_primary_dir(t_vector3 n)
{
	t_vector3 a;
	t_vector3 b;
	t_vector3 c;
	t_vector3 ab;

	a = vector3_cross(n, vector3_init(1, 0, 0));
	b = vector3_cross(n, vector3_init(0, 1, 0));
	c = vector3_cross(n, vector3_init(0, 0, 1));
	ab = vector3_dot(a, a) < vector3_dot(b, b) ? b : a;
	return (vector3_norm(vector3_dot(ab, ab) < vector3_dot(c, c) ? c : ab));
}

static void		plane_get_uv(t_vector3 p, t_vector3 n, double *u, double *v)
{
	t_vector3 uv;
	t_vector3 vv;
	int a;

	uv = compute_primary_dir(n);
	vv = vector3_cross(n, uv);
	*u = fabs(vector3_dot(uv, p));
	*v = fabs(vector3_dot(vv, p));
	a = *u;
	*u -= a;
	a = *v;
	*v -= a;
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
	plane_get_uv(result.p, plane->face, &result.u, &result.v);
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

