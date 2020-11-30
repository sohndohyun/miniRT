/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 19:29:45 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/30 22:00:32 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "triangle.h"
#include <stdio.h>

int		pinouttest(t_vector3 face, t_vector3 edge, t_vector3 vp)
{
	if (vector3_dot(face, vector3_cross(edge, vp)) < 0)
		return (0);
	return (1);
}

t_result		triangle_hit(void *obj, t_ray r, double t_min, double t_max)
{
	t_triangle *tr;
	double denom;
	t_result result;

	tr = obj;
	result.ret = 0;
	tr->face = vector3_cross(vector3_sbtr(tr->b, tr->a), vector3_sbtr(tr->c, tr->a));
	if ((denom = vector3_dot(tr->face, r.dir)) == 0)
		return (result);
	result.t = vector3_dot(vector3_sbtr(tr->a, r.orig), tr->face) / denom;
	if (result.t < t_min || t_max < result.t)
		return (result);
	result.p = ray_at(r, result.t);
	if (!pinouttest(tr->face, vector3_sbtr(tr->b, tr->a), vector3_sbtr(result.p, tr->a)) 
		|| !pinouttest(tr->face, vector3_sbtr(tr->c, tr->b), vector3_sbtr(result.p, tr->b)) 		|| !pinouttest(tr->face, vector3_sbtr(tr->a, tr->c), vector3_sbtr(result.p, tr->c)))
		return (result);
	result_set_face_normal(&result, r, tr->face);
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
