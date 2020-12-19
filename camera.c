/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 00:19:37 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/19 04:55:52 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "minirt.h"

static t_vector3	random_in_unit_disk(void)
{
	t_vector3 p;

	while (1)
	{
		p = vector3_init(random_range(-1, 1), random_range(-1, 1), 0);
		if (vector3_length_squared(p) > 1)
			continue;
		return (p);
	}
}

void				camera_setting(t_camera *camera, \
				double vfov, t_vector3 camera_set)
{
	camera->aspect_ratio = camera_set.x;
	camera->vp_height = 2.0 * tan(dtor(vfov) / 2);
	camera->vp_width = camera->vp_height * camera->aspect_ratio;
	camera->aperture = camera_set.y;
	camera->focus_dist = camera_set.z;
}

void				camera_transform(t_camera *c, \
				t_vector3 from, t_vector3 at, t_vector3 vup)
{
	c->w = vector3_norm(vector3_sbtr(from, at));
	c->u = vector3_norm(vector3_cross(vup, c->w));
	c->v = vector3_cross(c->w, c->u);
	c->origin = from;
	c->horizontal = vector3_mult(c->u, c->vp_width * c->focus_dist);
	c->vertical = vector3_mult(c->v, c->vp_height * c->focus_dist);
	c->ll_corner = vector3_init(
		c->origin.x - c->horizontal.x / 2 -
			c->vertical.x / 2 - c->w.x * c->focus_dist,
		c->origin.y - c->horizontal.y / 2 -
			c->vertical.y / 2 - c->w.y * c->focus_dist,
		c->origin.z - c->horizontal.z / 2 -
			c->vertical.z / 2 - c->w.z * c->focus_dist);
	c->lens_radius = c->aperture / 2;
}

t_ray				camera_getray(t_camera *c, double s, double t)
{
	t_vector3 rd;
	t_vector3 offset;

	rd = vector3_mult(random_in_unit_disk(), c->lens_radius);
	offset = vector3_add(vector3_mult(c->u, rd.x), vector3_mult(c->v, rd.y));
	return (ray_init(vector3_add(c->origin, offset),
		vector3_sbtr(vector3_add(
			vector3_add(c->ll_corner, vector3_mult(c->horizontal, s)),
			vector3_sbtr(vector3_mult(c->vertical, t), c->origin)), offset)));
}

void				camera_free(void *camera)
{
	t_camera *cam;

	cam = camera;
	free(cam);
}
