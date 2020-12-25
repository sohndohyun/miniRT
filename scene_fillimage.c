/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_fillimage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 22:00:52 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/26 00:31:29 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "minirt.h"
#include <stdio.h>

static t_vector3	filter_sepia(t_vector3 color)
{
	t_vector3 output;

	output.x = (color.x * 0.393) + (color.y * 0.769) + (color.z * 0.189);
	output.y = (color.x * 0.349) + (color.y * 0.686) + (color.z * 0.168);
	output.z = (color.x * 0.272) + (color.y * 0.534) + (color.z * 0.131);
	output.x = output.x > 0.999 ? 0.999 : output.x;
	output.y = output.y > 0.999 ? 0.999 : output.y;
	output.z = output.z > 0.999 ? 0.999 : output.z;
	return (output);
}

static unsigned int	vtoc(t_vector3 v, int samples_per_pixel, int ft)
{
	unsigned int color;

	v = vector3_div(v, samples_per_pixel);
	if (ft)
		v = filter_sepia(v);
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

static t_vector3	ray_color(t_ray r, t_scene *scene, int depth)
{
	t_vector3	temp;
	t_result	result;
	t_ray		scattered;
	t_vector3	emitted;

	if (depth <= 0)
		return (vector3_init(0, 0, 0));
	result = scene_hit(scene, r, 0.001, __DBL_MAX__);
	if (!result.ret)
		return (scene_background(scene, r));
	emitted = result.mat->emitted(result.mat->obj, &result);
	scattered = result.mat->scatter(
		result.mat->obj, r, &result, &temp);
	if (!result.ret)
		return (emitted);
	return (vector3_add(emitted, vector3_mult_vec(
		temp, ray_color(scattered, scene, depth - 1))));
}

static void			set_color(
	unsigned int *dst, t_scene *scene, int i, int j)
{
	t_vector3	pixel_color;
	int			k;
	int			ft;

	ft = scene->sepia_filter;
	pixel_color = vector3_init(0, 0, 0);
	k = 0;
	while (k < scene->sample_per_pixel)
	{
		pixel_color = vector3_add(pixel_color,
			ray_color(camera_getray(scene->cam,
			(random_double() + i) / (scene->screen_width - 1),
			(random_double() + j) / (scene->screen_height - 1)),
			scene, scene->max_depth));
		k++;
	}
	*dst = vtoc(pixel_color, scene->sample_per_pixel, ft);
}

void				scene_fillimage(t_mlx *mlx, int th_count, int th_no)
{
	int i;
	int j;
	int end;

	i = mlx->scene->screen_width * th_no / th_count;
	end = mlx->scene->screen_width * (th_no + 1) / th_count;
	while (i < end)
	{
		j = 0;
		while (j < mlx->scene->screen_height)
		{
			set_color((unsigned int*)(mlx->addr +
				(mlx->scene->screen_height - j - 1)
				* mlx->line + i * (mlx->bpp / 8)),
				mlx->scene, i, j);
			j++;
		}
		i++;
	}
}
