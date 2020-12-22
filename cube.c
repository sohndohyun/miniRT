/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 22:22:17 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/22 22:19:09 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <stdio.h>

t_result		cube_hit(void *obj, t_ray r, double t_min, double t_max)
{
	t_result	result;
	t_result	current;
	int			i;
	double		closet;
	t_hittable	**cube;

	cube = obj;
	i = 0;
	closet = t_max;
	result.ret = 0;
	while (i < 6)
	{
		current = cube[i]->hit(cube[i]->object, r, t_min, closet);
		if (current.ret == 1)
		{
			closet = current.t;
			result = current;
		}
		i++;
	}
	return (result);
}

t_hittable		*cube_alloc(
	t_vector3 center, double side, t_material *mat)
{
	t_hittable	*hit;
	t_hittable	**cube;
	t_ray		up;
	t_ray		front;
	t_ray		right;

	up = ray_init(center, vector3_init(0, 1, 0));
	front = ray_init(center, vector3_init(0, 0, 1));
	right = ray_init(center, vector3_init(1, 0, 0));
	cube = malloc(sizeof(t_hittable*) * 6);
	cube[0] = square_alloc(ray_at(up, side * -0.5), up.dir, side, mat);
	cube[1] = square_alloc(ray_at(up, side * 0.5), up.dir, side, mat);
	cube[2] = square_alloc(ray_at(front, side * -0.5), front.dir, side, mat);
	cube[3] = square_alloc(ray_at(front, side * 0.5), front.dir, side, mat);
	cube[4] = square_alloc(ray_at(right, side * -0.5), right.dir, side, mat);
	cube[5] = square_alloc(ray_at(right, side * 0.5), right.dir, side, mat);
	hit = malloc(sizeof(t_hittable));
	hit->hit = cube_hit;
	hit->object = cube;
	hit->del = cube_free;
	return (hit);
}

void			cube_free(void *cube)
{
	t_hittable	**temp;
	int			i;

	i = 0;
	temp = cube;
	while (i < 6)
	{
		temp[i]->del(temp[i]->object);
		i++;
	}
	free(temp);
}
