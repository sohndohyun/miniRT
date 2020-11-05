/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 20:44:29 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/05 21:47:50 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITTABLE_H
# define HITTABLE_H

#include "ray.h"
#include "libft.h"

typedef struct		s_hit_result
{
	t_vector3		p;
	t_vector3		norm;
	double			t;
	int				ret;
}					t_hit_result;

typedef struct		s_hittable
{
	void			*object;
	t_hit_result	(*hit)(void *obj, t_ray r, double t_min, double t_max);
}					t_hittable;

t_hit_result		hittable_hit(t_hittable *htbl, t_ray r, double t_min, double t_max);

#endif
