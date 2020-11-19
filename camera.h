/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 00:19:35 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/19 20:16:46 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

#include "minirt.h"

typedef struct	s_camera
{
	double		vp_height;
	double		vp_width;
	double		aspect_ratio;
	double		aperture;
	double		focus_dist;
	double		lens_radius;
	t_vector3	origin;
	t_vector3	ll_corner;
	t_vector3	horizontal;
	t_vector3	vertical;
	t_vector3	w;
	t_vector3	u;
	t_vector3	v;
}				t_camera;

void			camera_setting(t_camera *camera, double vfov, t_vector3 camera_set);
t_ray			camera_getray(t_camera *camera, double s, double t);
void			camera_transform(t_camera *camera, t_vector3 from, t_vector3 at, t_vector3 vup);

#endif
