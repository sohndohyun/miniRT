/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 17:02:08 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/19 04:41:58 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vector3.h"

typedef struct	s_ray
{
	t_vector3	orig;
	t_vector3	dir;
}				t_ray;

t_ray			ray_init(t_vector3 orig, t_vector3 dir);
t_vector3		ray_at(t_ray ray, double t);
int				ray_plane_t(t_ray ray, t_ray plane, double *t);

#endif
