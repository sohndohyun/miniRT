/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 01:31:58 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/25 21:35:08 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "readrt.h"
#include <stdio.h>

t_result	scene_hit(t_scene *scene,
	t_ray r, double t_min, double t_max)
{
	t_list		*it;
	t_hittable	*obj;
	t_result	result;
	t_result	current;
	double		closet;

	result.ret = 0;
	closet = t_max;
	it = scene->hittable_lst;
	while (it)
	{
		obj = it->content;
		current = obj->hit(obj->object, r, t_min, closet);
		if (current.ret == 1)
		{
			closet = current.t;
			result = current;
		}
		it = it->next;
	}
	return (result);
}

void		scene_add(t_scene *scene, t_hittable *object)
{
	ft_lstadd_back(&scene->hittable_lst, ft_lstnew(object));
}

void		scene_free(t_scene *scene)
{
	ft_lstclear(&scene->hittable_lst, hittable_free);
	ft_lstclear(&scene->camera_lst, camera_free);
}

void		scene_init(t_mlx *mlx,
	int sample_per_pixel, int max_depth, char *str)
{
	t_scene *scene;

	scene = mlx->scene;
	scene->hittable_lst = NULL;
	scene->camera_lst = NULL;
	scene->sample_per_pixel = sample_per_pixel;
	scene->max_depth = max_depth;
	scene->camera_no = 0;
	scene->sepia_filter = 0;
	scene->isbox = 0;
	readrt(scene, str, mlx->mlx);
}

t_vector3	scene_background(t_scene *scene, t_ray r)
{
	if (scene->isbox)
		return (skybox_background(&scene->skybox, r));
	return (scene->background);
}
