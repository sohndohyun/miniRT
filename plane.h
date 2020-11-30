/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 20:12:56 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/30 17:40:12 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "hittable.h"
# include "material.h"

typedef struct	s_plane
{
	t_vector3	orig;
	t_vector3	face;
	t_material	*mat;
}				t_plane;

t_result		plane_hit(void *obj, t_ray r, double t_min, double t_max);
t_hittable		*plane_alloc(t_vector3 orig, t_vector3 face, t_material *mat);
void			plane_free(void *plane);

#endif
