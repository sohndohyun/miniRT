/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:46:18 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/16 02:47:28 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "sphere.h"
#include "scene.h"
#include "camera.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450
#define SAMPLE_PER_PIXEL 100
#define MAX_DEPTH 50

typedef struct	s_image {
	void		*img;
	char		*addr;
	int			bpp;
	int			line;
	int			endian;
}				t_image;

unsigned int vtoc(t_vector3 v, int samples_per_pixel)
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

t_vector3 ray_color(t_ray r, t_scene *scene, int depth)
{
	t_vector3 dir;
	double t;
	t_result result;

	if (depth <= 0)
		return vector3_init(0, 0, 0);
	result = scene_hit(scene, r, 0.001, __DBL_MAX__);
	if (result.ret)
	{
		dir = vector3_add(result.p, vector3_random_hemisphere(result.norm));
		return vector3_mult(ray_color(ray_init(result.p, vector3_sbtr(dir, result.p)), scene, depth - 1), 0.5);
	}
	dir = vector3_norm(r.dir);
	t = 0.5 * (dir.y + 1.0);
	return (vector3_add(
		vector3_mult(vector3_init(1.0, 1.0, 1.0), 1.0 - t),
		vector3_mult(vector3_init(0.5, 0.7, 1.0), t)
	));
}

void fillimage(t_image *img, t_scene *scene, t_camera *cam)
{
	int i;
	int j;
	int k;
	char* dst;
	t_vector3 pixel_color;

	i = 0;
	while (i < SCREEN_WIDTH)
	{
		j = 0;
		while (j < SCREEN_HEIGHT)
		{
			dst = img->addr + (SCREEN_HEIGHT - j - 1) * img->line + i * (img->bpp / 8);
			pixel_color = vector3_init(0, 0, 0);
			k = 0;
			while (k < SAMPLE_PER_PIXEL)
			{
				pixel_color = vector3_add(pixel_color, ray_color(camera_getray(cam, \
					(random_double() + i) / (SCREEN_WIDTH - 1), \
					(random_double() + j) / (SCREEN_HEIGHT - 1)), scene, MAX_DEPTH));
				k++;
			}
			*(unsigned int*)dst = vtoc(pixel_color, SAMPLE_PER_PIXEL);
			j++;
		}
		i++;
	}
}

int main(void)
{
	void *mlx;
	void *window;
	t_image img;
	t_scene scene;
	t_camera cam;

	scene = NULL;
	mlx = mlx_init();
	window = mlx_new_window(mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "miniRT");
	img.img = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line, &img.endian);

	scene_add(&scene, sphere_alloc(vector3_init(0, 0, -10.0), 0.5));
	scene_add(&scene, sphere_alloc(vector3_init(1, 0, -10.0), 0.5));
	scene_add(&scene, sphere_alloc(vector3_init(-1, 0, -10.0), 0.5));
	scene_add(&scene, sphere_alloc(vector3_init(0.0, -100.5, -10.0), 100.0));
	camera_setting(&cam, (double)SCREEN_WIDTH / (double)SCREEN_HEIGHT, 2.0, 1.0);
	fillimage(&img, &scene, &cam);
	mlx_put_image_to_window(mlx, window, img.img, 0, 0);
	mlx_loop(mlx);
	scene_free(&scene);
	return (0);
}
