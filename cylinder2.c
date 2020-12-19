/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 13:24:43 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/19 15:24:13 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"

t_hittable		*cylinder_alloc(
	t_ray r, double radius, double height, t_material *mat)
{
	t_cylinder *cyl;
	t_hittable *hit;

	cyl = malloc(sizeof(t_cylinder));
	cyl->bottom = r.orig;
	cyl->face = r.dir;
	cyl->top = ray_at(r, height);
	cyl->radius = radius;
	cyl->height = height;
	cyl->mat = mat;
	hit = malloc(sizeof(t_hittable));
	hit->hit = cylinder_hit;
	hit->object = cyl;
	hit->del = cylinder_free;
	return (hit);
}

void			cylinder_free(void *cylinder)
{
	t_cylinder *temp;

	temp = cylinder;
	temp->mat->del(temp->mat->obj);
	free(temp->mat);
	free(temp);
}
