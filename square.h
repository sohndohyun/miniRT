/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 04:19:51 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/19 04:45:16 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SQUARE_H
# define SQUARE_H

# include "hittable.h"
# include "material.h"

typedef struct	s_square
{
	t_vector3	center;
	t_vector3	face;
	double		side;
	t_material	*mat;
}				t_square;

t_result		square_hit(void *obj, t_ray r, double t_min, double t_max);
t_hittable		*square_alloc(t_vector3 center, \
			t_vector3 face, double side, t_material *mat);
void			square_free(void *square);

#endif
