/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_fillimage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 22:00:52 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/21 00:33:32 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "minirt.h"

static unsigned int vtoc(t_vector3 v, int samples_per_pixel)
{
	unsigned int color;

	v = vector3_div(v, samples_per_pixel);
	v.x = sqrt(v.x);
	v.y = sqrt(v.y);
	v.z = sqrt(v.z);
	color = 0;
	color += (unsigned char)(256 * clamp(v.x, 0.0, 0.999));
	color <<= 8;
	color += (unsigned char)(256 * clamp(v.y, 0.0, 0.999));
	color <<= 8;
	color += (unsigned char)(256 * clamp(v.z, 0.0, 0.999));
	return (color);
}

static t_vector3 ray_color(t_ray r, t_scene *scene, int depth)
{
	t_vector3 temp;
	double t;
	t_result result;
	t_ray scattered;

	if (depth <= 0)
		return vector3_init(0, 0, 0);
	result = scene_hit(scene, r, 0.001, __DBL_MAX__);
	if (result.ret)
	{
		scattered = result.mat->scatter(result.mat->obj, r, &result, &temp);
		if (result.ret)
			return (vector3_mult_vec(temp, ray_color(scattered, scene, depth - 1)));
		return vector3_init(0, 0, 0);
	}
	temp = vector3_norm(r.dir);
	t = 0.5 * (temp.y + 1.0);
	return (vector3_add(
		vector3_mult(vector3_init(1.0, 1.0, 1.0), 1.0 - t),
		vector3_mult(vector3_init(0.5, 0.7, 1.0), t)
	));
}

static void set_color(unsigned int *dst, t_scene *scene, int i, int j)
{
	t_vector3 pixel_color;
	int k;

	pixel_color = vector3_init(0, 0, 0);
	k = 0;
	while (k < scene->sample_per_pixel)
	{
		pixel_color = vector3_add(pixel_color, ray_color(camera_getray(&scene->cam,
			(random_double() + i) / (scene->screen_width - 1),
			(random_double() + j) / (scene->screen_height - 1)), scene, scene->max_depth));
		k++;
	}
	*dst = vtoc(pixel_color, scene->sample_per_pixel);
}

void scene_fillimage(t_scene *scene, t_image *img, int th_count, int th_no)
{
	int i;
	int j;
	int end;

	i = scene->screen_width * th_no / th_count;
	end = scene->screen_width * (th_no + 1) / th_count;
	while (i < end)
	{
		j = 0;
		while (j < scene->screen_height)
		{
			set_color((unsigned int*)(img->addr + 
				(scene->screen_height - j - 1) * img->line + i * (img->bpp / 8)), scene, i, j);
			j++;
		}
		i++;
	}
}
