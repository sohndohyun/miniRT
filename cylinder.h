/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 03:14:16 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/19 13:50:34 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include "hittable.h"
# include "material.h"

typedef struct	s_cylinder
{
	t_vector3	top;
	t_vector3	bottom;
	t_vector3	face;
	double		radius;
	double		height;
	t_material	*mat;
}				t_cylinder;

typedef struct	s_cylval
{
	double		a;
	double		half_b;
	double		c;
	double		disc;
}				t_cylval;

t_result		cylinder_hit(void *obj, t_ray r, double t_min, double t_max);
t_hittable		*cylinder_alloc(t_ray r, double radius, \
			double height, t_material *mat);
void			cylinder_free(void *cylinder);

#endif
