/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:32:30 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/22 22:23:01 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pyramid.h"

t_result		pyramid_hit(void *obj, t_ray r, double t_min, double t_max)
{
	t_result	result;
	t_result	current;
	int			i;
	double		closet;
	t_hittable	**pyramid;

	pyramid = obj;
	i = 0;
	closet = t_max;
	result.ret = 0;
	while (i < 5)
	{
		current = pyramid[i]->hit(pyramid[i]->object, r, t_min, closet);
		if (current.ret == 1)
		{
			closet = current.t;
			result = current;
		}
		i++;
	}
	return (result);
}

void			set_point(
	t_vector3 *points, t_vector3 center, double height, double side)
{
	points[4] = vector3_add(center,
		vector3_mult(vector3_init(0, 1, 0), height));
	points[0] = vector3_add(center,
		vector3_mult(vector3_init(-1, 0, 1), side / 2));
	points[1] = vector3_add(center,
		vector3_mult(vector3_init(-1, 0, -1), side / 2));
	points[2] = vector3_add(center,
		vector3_mult(vector3_init(1, 0, -1), side / 2));
	points[3] = vector3_add(center,
		vector3_mult(vector3_init(1, 0, 1), side / 2));
}

t_hittable		*pyramid_alloc(
	t_vector3 center, double height, double side, t_material *mat)
{
	t_hittable	*hit;
	t_hittable	**pyr;
	t_vector3	points[5];

	set_point(points, center, height, side);
	pyr = malloc(sizeof(t_hittable*) * 5);
	pyr[0] = square_alloc(center, vector3_init(0, 1, 0), side, mat);
	pyr[1] = triangle_alloc(points[0], points[1], points[4], mat);
	pyr[2] = triangle_alloc(points[1], points[2], points[4], mat);
	pyr[3] = triangle_alloc(points[2], points[3], points[4], mat);
	pyr[4] = triangle_alloc(points[3], points[0], points[4], mat);
	hit = malloc(sizeof(t_hittable));
	hit->hit = pyramid_hit;
	hit->object = pyr;
	hit->del = pyramid_free;
	return (hit);
}

void			pyramid_free(void *cube)
{
	t_hittable	**temp;
	int			i;

	i = 0;
	temp = cube;
	while (i < 5)
	{
		temp[i]->del(temp[i]->object);
		i++;
	}
	free(temp);
}
