/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metal.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:57:14 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/19 04:37:23 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef METAL_H
# define METAL_H

# include "minirt.h"

typedef struct	s_metal
{
	t_vector3	albedo;
	double		fuzz;
}				t_metal;

t_ray			metal_scatter(void *obj, t_ray rin, \
			t_result *result, t_vector3 *color);
t_material		*metal_alloc(t_vector3 albedo, double f);
void			metal_free(void *metal);

#endif
