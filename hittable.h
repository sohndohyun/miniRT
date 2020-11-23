/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 20:44:29 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/23 20:12:09 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITTABLE_H
# define HITTABLE_H

#include "minirt.h"

struct 					s_material;

typedef struct			s_result
{
	t_vector3			p;
	t_vector3			norm;
	struct s_material	*mat;
	double				t;
	double				u;
	double				v;
	int					front_face;
	int					ret;
}						t_result;

typedef struct			s_hittable
{
	void				*object;
	t_result			(*hit)(void *obj, t_ray r, double t_min, double t_max);
	void				(*del)(void *obj);
}						t_hittable;

void					hittable_free(void *hittable);
void					result_set_face_normal(t_result *result, t_ray ray, t_vector3 outward_normal);

#endif
