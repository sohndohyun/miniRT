/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 00:19:35 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/15 00:50:50 by dsohn            ###   ########.fr       */
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
	double		focal_length;
	t_vector3	origin;
	t_vector3	ll_corner;
	t_vector3	horizontal;
	t_vector3	vertical;
}				t_camera;

void			camera_setting(t_camera *camera, double ratio, double vph, double flen);
t_ray			camera_getray(t_camera *camera, double u, double v);

#endif
