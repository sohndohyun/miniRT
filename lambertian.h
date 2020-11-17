/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lambertian.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 17:38:48 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/17 15:59:19 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAMBERTIAN_H
# define LAMBERTIAN_H

# include "minirt.h"

typedef struct	s_lambertian
{
	t_vector3	albedo;
}				t_lambertian;

t_ray			lambertian_scatter(void *obj, t_ray rin, t_result *result, t_vector3 *color);
t_material		*lambertian_alloc(t_vector3 albedo);
void			lambertian_free(void *lambertian);

#endif
