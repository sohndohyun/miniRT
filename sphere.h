/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 21:16:34 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/16 17:11:42 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "hittable.h"
# include "material.h"

typedef struct	s_sphere
{
	t_vector3	center;
	double		radius;
	t_material	*mat;
}				t_sphere;

t_result		sphere_hit(void *obj, t_ray r, double t_min, double t_max);
t_hittable		*sphere_alloc(t_vector3 center, double radius, t_material *mat);
void			sphere_free(void *sphere);

#endif
