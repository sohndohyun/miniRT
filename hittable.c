/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 02:04:30 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/28 21:15:55 by dsohn            ###   ########.fr       */
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
