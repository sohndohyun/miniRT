/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 04:22:32 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/24 04:22:38 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cone.h"

t_hittable		*cone_alloc(t_ray ray, \
	double angle, double height, t_material *mat)
{
	t_cone		*cone;
	t_hittable	*hit;

	cone = malloc(sizeof(t_cone));
	cone->angle = dtor(angle);
	cone->height = height;
	cone->cen = ray.orig;
	cone->dir = ray.dir;
	cone->mat = mat;
	hit = malloc(sizeof(t_hittable));
	hit->hit = cone_hit;
	hit->object = cone;
	hit->del = cone_free;
	return (hit);
}

void			cone_free(void *cone)
{
	t_cone *temp;

	temp = cone;
	temp->mat->del(temp->mat->obj);
	free(temp->mat);
	free(temp);
}
