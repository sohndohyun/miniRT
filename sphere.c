/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 21:33:41 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/12 02:43:15 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "sphere.h"
#include <stdlib.h>

t_result	sphere_hit(void *obj, t_ray r, double t_min, double t_max)
{
	t_sphere *sphere;
	t_result result;
	t_vector3 oc;
	double a;
	double b;
	double disc;
	double root;

	result.ret = 0;
	sphere = (t_sphere*)obj;
	oc = vector3_sbtr(r.orig, sphere->center); 
	a = vector3_length_squared(r.dir);
	b = vector3_dot(oc, r.dir);
	disc = b * b - a * (vector3_length_squared(oc) - sphere->radius * sphere->radius);
	if (disc < 0)
		return (result);
	disc = sqrt(disc);
	root = (-b - disc) / a;
	if (root < t_min || t_max < root)
	{
		root = (-b + disc) / a;
		if (root < t_min || t_max < root)
			return (result);
	}
	
	result.t = root;
	result.p = ray_at(r, root);
	oc = vector3_div(vector3_sbtr(result.p, sphere->center), sphere->radius);
	result_set_face_normal(&result, r, oc);
	result.ret = 1;
	return (result);
}

t_hittable		*sphere_alloc(t_vector3 center, double radius)
{
	t_sphere *sphere;
	t_hittable *hitable;

	sphere = malloc(sizeof(t_sphere));
	sphere->center = center;
	sphere->radius = radius;
	hitable = malloc(sizeof(t_hittable));
	hitable->hit = sphere_hit;
	hitable->object = (void*)sphere;
	return (hitable);
}