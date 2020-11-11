/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 02:04:30 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/11 16:20:22 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"

void	hittable_free(t_hittable *hittable)
{
	free(hittable->object);
	free(hittable);	
}

void	result_set_face_normal(t_result *result, t_ray ray, t_vector3 outward_normal)
{
	result->front_face = vector3_dot(ray.dir, outward_normal) < 0;
	result->norm = result->front_face ? outward_normal : vector3_not(outward_normal);
}
