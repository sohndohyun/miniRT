/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:46:18 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/11 04:08:24 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "sphere.h"
#include "scene.h"
#include "camera.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"
#include "solid_color.h"
#include "checker.h"
#include "dulight.h"
#include "plane.h"
#include "triangle.h"
#include "square.h"
#include "cylinder.h"
#include <time.h>
#include <stdio.h>

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 225
#define SAMPLE_PER_PIXEL 200
#define MAX_DEPTH 50

void sample_scene(t_scene *scene)
{
	scene_add(scene, plane_alloc(vector3_init(0, 0, 0), vector3_init(0, 1, 0), 
		lambertian_alloc(checker_alloc(vector3_init(1.0, 0.5, 0.5), vector3_init(0.5, 0.5, 1.0), 2))));
	scene_add(scene, cylinder_alloc(ray_init(vector3_init(0, 1.4, 2), vector3_init(1, 1, 1)), 1, 2, 
		lambertian_alloc(checker_alloc(vector3_init(0.5, 0.6, 0.99), vector3_init(0.99, 0.99, 0.99), 4))));
	scene_add(scene, sphere_alloc(vector3_init(0, 1.4, -2), 1, 
		lambertian_alloc(checker_alloc(vector3_init(0.5, 0.6, 0.99), vector3_init(0.99, 0.99, 0.99), 4))));
	scene->background = vector3_init(0.5, 0.7, 1.0);
}

void random_scene(t_scene *scene)
{
	int i;
	int j;
	double choose_mat;
	t_vector3 center;

	ft_srand(time(NULL));
	scene_add(scene, plane_alloc(vector3_init(0, 0, 0), vector3_init(0, 1, 0), 
		lambertian_alloc(checker_alloc(vector3_init(1.0, 1.0, 1.0), vector3_init(0.2, 0.2, 0.2), 100))));
	for (i = -11;i < 11;i++)
	{
		for (j = -11;j < 11;j++)
		{
			choose_mat = random_double();
			center = vector3_init(i + 0.9 * random_double(), 0.2, j + 0.9 * random_double());
			if (vector3_length(vector3_sbtr(center, vector3_init(4, 0.2, 0))) > 0.9)
			{
				if (choose_mat < 0.5)
					scene_add(scene, sphere_alloc(center, 0.2, lambertian_alloc(solid_color_alloc(vector3_random_range(0, 1)))));
				else if (choose_mat < 0.85)
					scene_add(scene, sphere_alloc(center, 0.2, metal_alloc(vector3_random_range(0.5, 1), random_range(0, 0.5))));
				else 
					scene_add(scene, sphere_alloc(center, 0.2, dielectric_alloc(1.5)));
			}
		}
	}

	scene_add(scene, sphere_alloc(vector3_init(0, 1, 0), 1, dielectric_alloc(1.5)));
	scene_add(scene, sphere_alloc(vector3_init(-4, 1, 0), 1, lambertian_alloc(solid_color_alloc((vector3_init(0.4, 0.2, 0.1))))));
	scene_add(scene, sphere_alloc(vector3_init(0, 1, 2), 1, metal_alloc(vector3_init(0.7, 0.6, 0.5), 0.0)));
	
	scene_add(scene, sphere_alloc(vector3_init(4, 1, 0), 1, 
		lambertian_alloc(checker_alloc(vector3_init(1.0, 1.0, 1.0), vector3_init(0.2, 0.2, 0.2), 10))));
	scene->background = vector3_init(0, 0, 0);
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

	lookfrom = vector3_init(10, 14, 0);
	lookat = vector3_init(0, 0, 0);
	vup = vector3_init(0, 1, 0);
	dist_to_focus = 10;
	aperture = 0.01;

	camera_setting(&scene.cam, 20, vector3_init((double)SCREEN_WIDTH / (double)SCREEN_HEIGHT, aperture, dist_to_focus));
	camera_transform(&scene.cam, lookfrom, lookat, vup);

	scene.hittable_lst = NULL;
	scene.screen_width = SCREEN_WIDTH;
	scene.screen_height = SCREEN_HEIGHT;
	scene.sample_per_pixel = SAMPLE_PER_PIXEL;
	scene.max_depth = MAX_DEPTH;
//	random_scene(&scene);
	sample_scene(&scene);
//	scene_add(&scene, plane_alloc(vector3_init(0, 0, 0), vector3_init(0, -1, 0), 
//		lambertian_alloc(checker_alloc(vector3_init(1, 1, 1), vector3_init(0.2, 0.2, 0.2)))));	
	scene_render(&scene, &img);

	mlx_put_image_to_window(mlx, window, img.img, 0, 0);
	mlx_loop(mlx);
	scene_free(&scene);

	return (0);
}
