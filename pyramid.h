/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramid.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:32:27 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/22 22:30:45 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PYRAMID_H
# define PYRAMID_H

# include "square.h"
# include "triangle.h"

t_result		pyramid_hit(void *obj, t_ray r, double t_min, double t_max);
t_hittable		*pyramid_alloc(t_vector3 center, \
	double height, double side, t_material *mat);
void			pyramid_free(void *cube);

#endif
