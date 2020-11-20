/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:46:18 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/21 00:53:47 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "sphere.h"
#include "scene.h"
#include "camera.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"
#include <time.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define SAMPLE_PER_PIXEL 30
#define MAX_DEPTH 20

void random_scene(t_scene *scene)
{
	int i;
	int j;
	double choose_mat;
	t_vector3 center;

	ft_srand(time(NULL));
	scene_add(scene, sphere_alloc(vector3_init(0, -1000, 0), 1000, lambertian_alloc(vector3_init(0.5, 0.5, 0.5))));
	
	for (i = -11;i < 11;i++)
	{
		for (j = -11;j < 11;j++)
		{
			choose_mat = random_double();
			center = vector3_init(i + 0.9 * random_double(), 0.2, j + 0.9 * random_double());
			if (vector3_length(vector3_sbtr(center, vector3_init(4, 0.2, 0))) > 0.9)
			{
				if (choose_mat < 0.8)
					scene_add(scene, sphere_alloc(center, 0.2, lambertian_alloc(vector3_random_range(0, 1))));
				else if (choose_mat < 0.95)
					scene_add(scene, sphere_alloc(center, 0.2, metal_alloc(vector3_random_range(0.5, 1), random_range(0, 0.5))));
				else
					scene_add(scene, sphere_alloc(center, 0.2, dielectric_alloc(1.5)));
			}
		}
	}

	scene_add(scene, sphere_alloc(vector3_init(0, 1, 0), 1, dielectric_alloc(1.5)));
	scene_add(scene, sphere_alloc(vector3_init(-4, 1, 0), 1, lambertian_alloc(vector3_init(0.4, 0.2, 0.1))));
	scene_add(scene, sphere_alloc(vector3_init(4, 1, 0), 1, metal_alloc(vector3_init(0.7, 0.6, 0.5), 0.0)));
}

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
				pixel_color = vector3_add(pixel_color, ray_color(camera_getray(cam,
					(random_double() + i) / (SCREEN_WIDTH - 1),
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
 
	t_vector3 lookfrom;
	t_vector3 lookat;
	t_vector3 vup;
	double dist_to_focus;
	double aperture;

	mlx = mlx_init();
	window = mlx_new_window(mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "miniRT");
	img.img = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line, &img.endian);

	lookfrom = vector3_init(13, 2, 3);
	lookat = vector3_init(0, 0, 0);
	vup = vector3_init(0, 1, 0);
	dist_to_focus = 10;
	aperture = 0.01;

	camera_setting(&scene.cam, 20, vector3_init((double)SCREEN_WIDTH / (double)SCREEN_HEIGHT, aperture, dist_to_focus));
	camera_transform(&scene.cam, lookfrom, lookat, vup);

	scene.screen_width = SCREEN_WIDTH;
	scene.screen_height = SCREEN_HEIGHT;
	scene.sample_per_pixel = SAMPLE_PER_PIXEL;
	scene.max_depth = MAX_DEPTH;
	random_scene(&scene);
	//fillimage(&img, &scene, &cam);
	scene_render(&scene, &img);

	mlx_put_image_to_window(mlx, window, img.img, 0, 0);
	mlx_loop(mlx);
	scene_free(&scene);
	return (0);
}
