/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 00:19:37 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/15 04:56:31 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

void	camera_setting(t_camera *camera, double ratio, double vph, double flen)
{
	camera->aspect_ratio = ratio;
	camera->vp_height = vph;
	camera->vp_width = vph * ratio;
	camera->focal_length = flen;
	camera->origin = vector3_init(0, 0, 0);
	camera->horizontal = vector3_init(camera->vp_width, 0.0, 0.0);
	camera->vertical = vector3_init(0.0, camera->vp_height, 0.0);
	camera->ll_corner = vector3_init(
		camera->origin.x - camera->horizontal.x / 2 - camera->vertical.x / 2,
		camera->origin.y - camera->horizontal.y / 2 - camera->vertical.y / 2,
		camera->origin.z - camera->horizontal.z / 2 - camera->vertical.z / 2 - camera->focal_length
	);
}

t_ray	camera_getray(t_camera *camera, double u, double v)
{
	return (ray_init(camera->origin, 
		vector3_add(
			vector3_add(camera->ll_corner, vector3_mult(camera->horizontal, u)), 
			vector3_sbtr(vector3_mult(camera->vertical, v), camera->origin)
		)
	));
}
