/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 21:33:41 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/19 18:50:57 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"

static void		sphere_get_uv(t_vector3 p, double *u, double *v)
{
	double phi;
	double theta;

	phi = atan2(-p.z, p.x) + PI;
	theta = acos(-p.y);
	*u = phi / (2 * PI);
	*v = theta / PI;
}

static void		calculate(t_sphere *sphere, t_ray r, t_fvalue *val)
{
	val->oc = vector3_add(r.orig, vector3_not(sphere->center));
	val->a = vector3_length_squared(r.dir);
	val->half_b = vector3_dot(val->oc, r.dir);
	val->c = vector3_length_squared(val->oc) -
		(sphere->radius * sphere->radius);
	val->disc = (val->half_b * val->half_b) - (val->a * val->c);
}

t_result		sphere_hit(void *obj, t_ray r, double t_min, double t_max)
{
	t_sphere	*sphere;
	t_result	result;
	t_fvalue	val;

	result.ret = 0;
	sphere = (t_sphere*)obj;
	calculate(sphere, r, &val);
	if (val.disc < 0)
		return (result);
	val.sqrtd = sqrt(val.disc);
	result.t = (-val.half_b - val.sqrtd) / val.a;
	if (result.t < t_min || t_max < result.t)
	{
		result.t = (-val.half_b + val.sqrtd) / val.a;
		if (result.t < t_min || t_max < result.t)
			return (result);
	}
	result.p = ray_at(r, result.t);
	val.oc = vector3_div(vector3_sbtr(
		result.p, sphere->center), sphere->radius);
	result_set_face_normal(&result, r, val.oc);
	sphere_get_uv(val.oc, &result.u, &result.v);
	result.mat = sphere->mat;
	result.ret = 1;
	return (result);
}

t_hittable		*sphere_alloc(t_vector3 center, double radius, t_material *mat)
{
	t_sphere	*sphere;
	t_hittable	*hit;

	sphere = malloc(sizeof(t_sphere));
	sphere->center = center;
	sphere->radius = radius;
	sphere->mat = mat;
	hit = malloc(sizeof(t_hittable));
	hit->hit = sphere_hit;
	hit->object = sphere;
	hit->del = sphere_free;
	return (hit);
}

void			sphere_free(void *sphere)
{
	t_sphere	*temp;

	temp = sphere;
	temp->mat->del(temp->mat->obj);
	free(temp->mat);
	free(temp);
}
