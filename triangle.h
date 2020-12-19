/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:32:05 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/19 20:22:34 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGLE_H
# define TRIANGLE_H

# include "hittable.h"
# include "material.h"

typedef struct	s_triangle
{
	t_vector3	a;
	t_vector3	b;
	t_vector3	c;
	t_vector3	face;
	t_material	*mat;
}				t_triangle;

t_result		triangle_hit(void *obj, t_ray r, double t_min, double t_max);
t_hittable		*triangle_alloc(t_vector3 a, t_vector3 b, \
			t_vector3 c, t_material *mat);
void			triangle_free(void *triangle);
void			triangle_get_uv(double *u, double *v, double denom);
int				pot(t_vector3 face, t_vector3 edge, t_vector3 vp, double *uv);

#endif
