/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dielectric.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 21:10:22 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/19 04:33:42 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIELECTRIC_H
# define DIELECTRIC_H

# include "minirt.h"

typedef struct	s_dielectric
{
	double ir;
}				t_dielectric;

t_ray			dielectric_scatter(void *obj, t_ray rin, \
			t_result *result, t_vector3 *color);
t_material		*dielectric_alloc(double ir);
void			dielectric_free(void *dielectric);

#endif
