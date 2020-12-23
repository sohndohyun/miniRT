/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 02:16:37 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/24 01:40:18 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONE_H
# define CONE_H

# include "hittable.h"
# include "material.h"

typedef struct	s_cone
{
	t_vector3	cen;
	t_vector3	dir;
	double		angle;
	double		height;
	t_material	*mat;
}				t_cone;

typedef struct	s_conval
{
	double		a;
	double		b;
	double		c;
	double		disc;
	double		sqrtd;
}				t_conval;

t_result		cone_hit(void *obj, t_ray r, double t_min, double t_max);
t_hittable		*cone_alloc(t_ray ray, \
	double angle, double height, t_material *mat);
void			cone_free(void *cone);

#endif
