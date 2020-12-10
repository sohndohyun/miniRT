/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 19:29:45 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/03 05:12:11 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "triangle.h"
#include <stdio.h>

static void		triangle_get_uv(double *u, double *v, double denom)
{
	*u = *u / denom;
	*v = *v / denom;
}

int		pinouttest(t_vector3 face, t_vector3 edge, t_vector3 vp, double *uv)
{
	if ((*uv = vector3_dot(face, vector3_cross(edge, vp))) < 0)
		return (0);
	return (1);
}

t_result		triangle_hit(void *obj, t_ray r, double t_min, double t_max)
{
	t_triangle *tr;
	double denom;
	t_result result;
	double temp;

	tr = obj;
	result.ret = 0;
	tr->face = vector3_cross(vector3_sbtr(tr->b, tr->a), vector3_sbtr(tr->c, tr->a));
	if ((temp = vector3_dot(tr->face, r.dir)) == 0)
		return (result);
	result.t = vector3_dot(vector3_sbtr(tr->a, r.orig), tr->face) / temp;
	if (result.t < t_min || t_max < result.t)
		return (result);
	result.p = ray_at(r, result.t);
	if (!pinouttest(tr->face, vector3_sbtr(tr->b, tr->a), vector3_sbtr(result.p, tr->a), &temp) 
		|| !pinouttest(tr->face, vector3_sbtr(tr->c, tr->b), vector3_sbtr(result.p, tr->b), &result.u)
		|| !pinouttest(tr->face, vector3_sbtr(tr->a, tr->c), vector3_sbtr(result.p, tr->c), &result.v))
		return (result);
	result_set_face_normal(&result, r, tr->face);
	denom = vector3_dot(tr->face, tr->face);
	triangle_get_uv(&result.u, &result.v, denom);
	result.mat= tr->mat;
	result.ret = 1;
	return (result);
}

t_hittable		*triangle_alloc(t_vector3 a, t_vector3 b, t_vector3 c, t_material *mat)
{
	t_triangle *triangle;
	t_hittable *hit;

	triangle = malloc(sizeof(t_triangle));
	triangle->a = a;
	triangle->b = b;
	triangle->c = c;
	triangle->mat = mat;
	hit = malloc(sizeof(t_hittable));
	hit->hit = triangle_hit;
	hit->object = triangle;
	hit->del = triangle_free;
	return (hit);
}

void			triangle_free(void *triangle)
{
	t_triangle *temp;

	temp = triangle;
	temp->mat->del(temp->mat->obj);
	free(temp->mat);
	free(temp);
}
