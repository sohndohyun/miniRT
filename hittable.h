/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 20:44:29 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/11 16:18:22 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITTABLE_H
# define HITTABLE_H

#include "ray.h"
#include "libft.h"

typedef struct		s_result
{
	t_vector3		p;
	t_vector3		norm;
	double			t;
	int				front_face;
	int				ret;
}					t_result;

typedef struct		s_hittable
{
	void			*object;
	t_result		(*hit)(void *obj, t_ray r, double t_min, double t_max);
}					t_hittable;

void	hittable_free(t_hittable *hittable);
void	result_set_face_normal(t_result *result, t_ray ray, t_vector3 outward_normal);

#endif
