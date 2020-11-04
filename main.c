/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:46:18 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/04 22:02:47 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "ray.h"
#include "vector3.h"
#include <stdio.h>

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

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
	cam.viewport_width = SCREEN_WIDTH / SCREEN_HEIGHT * height;
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


t_vector3 ray_color(t_ray r)
{
	t_vector3 dir;
	double t;

	dir = vector3_norm(r.dir);
	t = 0.5 * (dir.y + 1.0);
	return (vector3_add(
		vector3_mult(vector3_init(0.0, 0.0, 1.0), 1.0 - t),
		vector3_mult(vector3_init(1.0, 0.0, 0.0), t)
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
			dst = img->addr + j * img->line + i * (img->bpp / 8);
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
