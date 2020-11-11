/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 21:16:34 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/12 02:43:16 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "hittable.h"

typedef struct	s_sphere
{
	t_vector3	center;
	double		radius;
}				t_sphere;

t_result		sphere_hit(void *obj, t_ray r, double t_min, double t_max);
t_hittable		*sphere_alloc(t_vector3 center, double radius);

#endif
