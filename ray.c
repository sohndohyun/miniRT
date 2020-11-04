/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 17:24:22 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/04 17:26:23 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_ray			ray_init(t_vector3 orig, t_vector3 dir)
{
	t_ray temp;

	temp.dir = dir;
	temp.orig = orig;
	return (temp);
}

t_vector3		ray_at(t_ray ray, double t)
{
	return (vector3_add(ray.orig, vector3_mult(ray.dir, t)));
}
