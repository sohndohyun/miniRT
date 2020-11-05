/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:46:18 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/05 20:20:39 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "ray.h"
#include "vector3.h"
#include <stdio.h>
#include <math.h>

#define SCREEN_WIDTH 711
#define SCREEN_HEIGHT 400

typedef struct	s_image {
	void		*img;
	char		*addr;
	int			bpp;
	int			line;
	int			endian;
}				t_image;

typedef struct	s_camera 
{
	double viewport_height;
	double viewport_width;
	double focal_length;
	t_vector3 origin;
	t_vector3 horizontal;
	t_vector3 vertical;
	t_vector3 lower_left_corner;
}				t_camera;

t_camera camera_init(t_vector3 origin, double height, double focal_length)
{
	t_camera cam;

	cam.viewport_height = height;
	cam.viewport_width = ((double)SCREEN_WIDTH / (double)SCREEN_HEIGHT) * height;
	cam.focal_length = focal_length;
	cam.origin = origin;
	cam.horizontal = vector3_init(cam.viewport_width, 0, 0);
	cam.vertical = vector3_init(0, height, 0);
	cam.lower_left_corner = vector3_init(
		origin.x - cam.viewport_width / 2,
		origin.y - height / 2,
		origin.z - focal_length
	);
	return (cam);
}

unsigned int vtoc(t_vector3 v)
{
	unsigned int color;

	color = 0;
	color += (unsigned char)(255.999 * v.x);
	color <<= 8;
	color += (unsigned char)(255.999 * v.y);
	color <<= 8;
	color += (unsigned char)(255.999 * v.z);
	return (color);
}

double hit_sphere(t_vector3 center, double radius, t_ray r)
{
	t_vector3 oc;
	double a;
	double half_b;
	double c;
	double discriminant;
	
	oc = vector3_add(r.orig, vector3_not(center));
	a = vector3_length_squared(r.dir);
	half_b = vector3_dot(oc, r.dir);
	c = vector3_length_squared(oc) - radius * radius;
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (-1.0);
	else 
		return ((-half_b - sqrt(discriminant)) / a);
}

t_vector3 ray_color(t_ray r)
{
	t_vector3 dir;
	double t;

	t = hit_sphere(vector3_init(0, 0, -1), 0.5, r);
	if (t > 0.0)
	{
		dir = vector3_norm(vector3_sbtr(ray_at(r, t), vector3_init(0, 0, -1)));
		return vector3_mult(vector3_init(dir.x + 1, dir.y + 1, dir.z + 1), 0.5);
	}
	dir = vector3_norm(r.dir);
	t = 0.5 * (dir.y + 1.0);
	return (vector3_add(
		vector3_mult(vector3_init(1.0, 1.0, 1.0), 1.0 - t),
		vector3_mult(vector3_init(0.5, 0.7, 1.0), t)
	));
}

void fillimage(t_image *img)
{
	int i;
	int j;
	char* dst;
	t_camera cam;

	cam = camera_init(vector3_init(0, 0, 0), 2.0, 1.0);
	i = 0;
	j = 0;
	while (i < SCREEN_WIDTH)
	{
		while (j < SCREEN_HEIGHT)
		{
			dst = img->addr + (SCREEN_HEIGHT - j - 1) * img->line + i * (img->bpp / 8);
			*(unsigned int*)dst = vtoc(ray_color(ray_init(cam.origin, vector3_init(
				cam.lower_left_corner.x + cam.horizontal.x * i / (SCREEN_WIDTH - 1) + cam.vertical.x * j / (SCREEN_HEIGHT - 1) - cam.origin.x,
				cam.lower_left_corner.y + cam.horizontal.y * i / (SCREEN_WIDTH - 1) + cam.vertical.y * j / (SCREEN_HEIGHT - 1) - cam.origin.y,
				cam.lower_left_corner.z + cam.horizontal.z * i / (SCREEN_WIDTH - 1) + cam.vertical.z * j / (SCREEN_HEIGHT - 1) - cam.origin.z
			))));
			j++;
		}
		i++;
		j = 0;
	}
}

int main(void)
{
	void *mlx;
	void *window;
	t_image img;

	mlx = mlx_init();
	window = mlx_new_window(mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "miniRT");
	img.img = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line, &img.endian);
	fillimage(&img);
	mlx_put_image_to_window(mlx, window, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
