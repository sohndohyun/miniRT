/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 17:02:08 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/04 17:04:45 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

#include "vector3.h"

typedef struct	s_ray
{
	t_vector3	orig;
	t_vector3	dir;
}				t_ray;

t_ray			ray_init(t_vector3 orig, t_vector3 dir);
t_vector3		ray_at(t_ray ray, double t);

#endif