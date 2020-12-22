/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 22:06:38 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/22 22:19:39 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder_bonus.h"

t_result		cylinder_bonus_hit(
	void *obj, t_ray r, double t_min, double t_max)
{
	t_result	result;
	t_result	current;
	int			i;
	double		closet;
	t_hittable	**cyl;

	cyl = obj;
	i = 0;
	closet = t_max;
	result.ret = 0;
	while (i < 3)
	{
		current = cyl[i]->hit(cyl[i]->object, r, t_min, closet);
		if (current.ret == 1)
		{
			closet = current.t;
			result = current;
		}
		i++;
	}
	return (result);
}

t_hittable		*cylinder_bonus_alloc(t_ray r, double radius, \
			double height, t_material *mat)
{
	t_hittable *hit;
	t_hittable **cyl;

	cyl = malloc(sizeof(t_hittable*) * 3);
	cyl[0] = cylinder_alloc(r, radius, height, mat);
	cyl[1] = disk_alloc(r.orig, r.dir, radius, mat);
	cyl[2] = disk_alloc(ray_at(r, height), r.dir, radius, mat);
	hit = malloc(sizeof(t_hittable));
	hit->hit = cylinder_bonus_hit;
	hit->object = cyl;
	hit->del = cylinder_bonus_free;
	return (hit);
}

void			cylinder_bonus_free(void *cylinder)
{
	t_hittable	**temp;
	int			i;

	i = 0;
	temp = cylinder;
	while (i < 3)
	{
		temp[i]->del(temp[i]->object);
		i++;
	}
	free(temp);
}
