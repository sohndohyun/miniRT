/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 02:04:30 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/02 15:03:33 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"
#include <stdlib.h>

void	hittable_free(void *hittable)
{
	t_hittable *temp;

	temp = (t_hittable*)hittable;
	temp->del(temp->object);
	if (temp)
		free(temp);	
}

void	result_set_face_normal(t_result *result, t_ray ray, t_vector3 outward_normal)
{
	result->front_face = vector3_dot(ray.dir, outward_normal) < 0.0;
	result->norm = vector3_norm(result->front_face ? outward_normal : vector3_not(outward_normal));
}

t_vector3	compute_primary_dir(t_vector3 n)
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
