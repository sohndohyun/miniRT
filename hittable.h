/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 20:44:29 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/05 21:03:39 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITTABLE_H
# define HITTABLE_H

#include "ray.h"
#include "libft.h"

typedef struct	s_hit_result
{
	t_vector3	p;
	t_vector3	norm;
	double		t;
}				t_hit_result;

typedef struct	s_hittable
{
	void*		object;
	int			(*hit)(t_ray r, double t_min, double t_max, t_hit_result *result);
}				t_hittable

#endif
