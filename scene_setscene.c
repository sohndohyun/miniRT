/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_setscene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 02:56:18 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/19 03:30:09 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include <stdio.h>

void	scene_setsize(t_scene *scene, int width, int height)
{
	scene->screen_width = width;
	scene->screen_height = height;
}

void	scene_setamblight(t_scene *scene, double range, t_vector3 color)
{
	scene->background = vector3_mult(color, range);
}

void	scene_setcamera(t_scene *scene, t_vector3 pos, t_vector3 face, double fov)
{
	t_camera *cam;

	cam = malloc(sizeof(t_camera));
	camera_setting(cam, fov, vector3_init(
		(double)scene->screen_width / (double)scene->screen_height, 0.01, 10));
	camera_transform(cam, pos, vector3_add(pos, face), vector3_init(0, 1, 0));
	ft_lstadd_back(&scene->camera_lst, ft_lstnew(cam));
}

