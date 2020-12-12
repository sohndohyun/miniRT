/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:46:18 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/12 02:42:10 by dsohn            ###   ########.fr       */
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

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 128
#define SAMPLE_PER_PIXEL 4096
#define MAX_DEPTH 32

void sample_scene(t_scene *scene)
{
	t_vector3 lookfrom;
	t_vector3 lookat;
	t_vector3 vup;
	double dist_to_focus;
	double aperture;
	
	lookfrom = vector3_init(14, 5, 0);
	lookat = vector3_init(0, 0, 0);
	vup = vector3_init(0, 1, 0);
	dist_to_focus = 10;
	aperture = 0.01;
	camera_setting(&scene->cam, 20, vector3_init((double)SCREEN_WIDTH / (double)SCREEN_HEIGHT, aperture, dist_to_focus));
	camera_transform(&scene->cam, lookfrom, lookat, vup);
	scene->hittable_lst = NULL;
	scene->screen_width = SCREEN_WIDTH;
	scene->screen_height = SCREEN_HEIGHT;
	scene->sample_per_pixel = SAMPLE_PER_PIXEL;
	scene->max_depth = MAX_DEPTH;
	scene_add(scene, plane_alloc(vector3_init(0, 0, 0), vector3_init(0, 1, 0), 
		lambertian_alloc(checker_alloc(vector3_init(1.0, 0.5, 0.5), vector3_init(0.5, 0.5, 1.0), 2))));
	scene_add(scene, cylinder_alloc(ray_init(vector3_init(0, 1.4, 2), vector3_init(1, 1, 1)), 1, 2, 
		lambertian_alloc(checker_alloc(vector3_init(0.5, 0.6, 0.99), vector3_init(0.99, 0.99, 0.99), 4))));
	scene_add(scene, sphere_alloc(vector3_init(0, 1.4, -2), 1, 
		lambertian_alloc(checker_alloc(vector3_init(0.5, 0.6, 0.99), vector3_init(0.99, 0.99, 0.99), 4))));
	scene_add(scene, sphere_alloc(vector3_init(17, 3, 0), 3, dulight_alloc(solid_color_alloc(vector3_init(4, 4, 4)))));
	scene_add(scene, sphere_alloc(vector3_init(-5, 6, 0), 3, dulight_alloc(solid_color_alloc(vector3_init(4, 4, 4)))));
	scene->background = vector3_init(0.0, 0.0, 0.0);
}

int main(void)
{
	void *mlx;
	void *window;
	t_image img;
	t_scene scene;

	sample_scene(&scene);
	mlx = mlx_init();
	window = mlx_new_window(mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "miniRT");
	img.img = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line, &img.endian);
	scene_render(&scene, &img);
	mlx_put_image_to_window(mlx, window, img.img, 0, 0);
	mlx_loop(mlx);
	scene_free(&scene);
	return (0);
}
