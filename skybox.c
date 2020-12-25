/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 14:27:56 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/26 00:31:05 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skybox.h"
#include <math.h>

#define UP		0
#define DOWN	1
#define FRONT	2
#define BACK	3
#define RIGHT	4
#define LEFT	5

void				skybox_init(t_skybox *b, char **line, void *mlx)
{
	rimage_init(&b->img[0], mlx, line[0]);
	rimage_init(&b->img[1], mlx, line[1]);
	rimage_init(&b->img[2], mlx, line[2]);
	rimage_init(&b->img[3], mlx, line[3]);
	rimage_init(&b->img[4], mlx, line[4]);
	rimage_init(&b->img[5], mlx, line[5]);
}

static t_vector3	get_sky_color(t_rimage *img, double x, double y, double max)
{
	return (rimage_color(img, 0.5 * (x / max + 1), 0.5 * (y / max + 1)));
}

t_vector3			skybox_background(t_skybox *b, t_ray r)
{
	double x;
	double y;
	double z;

	x = fabs(r.dir.x);
	y = fabs(r.dir.y);
	z = fabs(r.dir.z);
	if (z > x && z > y && r.dir.z >= 0)
		return (get_sky_color(&b->img[FRONT], r.dir.x, -r.dir.y, z));
	else if (z > x && z > y && r.dir.z < 0)
		return (get_sky_color(&b->img[BACK], -r.dir.x, -r.dir.y, z));
	else if (x > y && x > z && r.dir.x >= 0)
		return (get_sky_color(&b->img[RIGHT], -r.dir.z, -r.dir.y, x));
	else if (x > y && x > z && r.dir.x < 0)
		return (get_sky_color(&b->img[LEFT], r.dir.z, -r.dir.y, x));
	else if (y > x && y > z && r.dir.y >= 0)
		return (get_sky_color(&b->img[UP], r.dir.x, -r.dir.z, y));
	else if (y > x && y > z && r.dir.y < 0)
		return (get_sky_color(&b->img[DOWN], r.dir.x, r.dir.z, y));
	else
		return ((t_vector3){0, 0, 0});
}
