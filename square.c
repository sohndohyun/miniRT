/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 04:28:41 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/06 01:52:20 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "square.h"

static void		square_get_xy(t_vector3 p, t_vector3 n, double *x, double *y)
{
	t_vector3 uv;
	t_vector3 vv;

	uv = compute_primary_dir(n);
	vv = vector3_cross(n, uv);
	*x = vector3_dot(uv, p);
	*y = vector3_dot(vv, p);
}

static void		square_get_uv(double *u, double *v, double side)
{
	*u = (*u + side) / (side * 2);
	*v = (*v + side) / (side * 2);
}

t_result		square_hit(void *obj, t_ray r, double t_min, double t_max)
{
	t_square *square;
	t_result result;
	double denom;

	result.ret = 0;
	square = obj;
	if ((denom = vector3_dot(square->face, r.dir)) == 0)
		return (result);
	result.t = vector3_dot(vector3_sbtr(square->center, r.orig), vector3_norm(square->face)) / denom;
	if (result.t < t_min || t_max < result.t)
		return (result);
	result.p = ray_at(r, result.t);
	result_set_face_normal(&result, r, square->face);
	square_get_xy(vector3_sbtr(square->center, result.p), square->face, &result.u, &result.v);
	denom = square->side / 2;
	if ((result.u < -denom || denom < result.u) || (result.v < -denom || denom < result.v))
		return (result);
	square_get_uv(&result.u, &result.v, denom);
	result.mat = square->mat;
	result.ret = 1;
	return (result);
}

t_hittable		*square_alloc(t_vector3 center, t_vector3 face, double side, t_material *mat)
{
	t_square *square;
	t_hittable *hit;

	square = malloc(sizeof(t_square));
	square->center = center;
	square->face = face;
	square->side = side;
	square->mat = mat;
	hit = malloc(sizeof(t_hittable));
	hit->hit = square_hit;
	hit->object = square;
	hit->del = square_free;
	return (hit);
}

void			square_free(void *square)
{
	t_square *temp;

	temp = square;
	temp->mat->del(temp->mat->obj);
	free(temp->mat);
	free(temp);
}
