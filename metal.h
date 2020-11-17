/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metal.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:57:14 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/17 22:16:00 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef METAL_H
# define METAL_H

# include "minirt.h"

typedef struct	s_metal
{
	t_vector3 albedo;;
}				t_metal;

t_ray			metal_scatter(void *obj, t_ray rin, t_result *result, t_vector3 *color);
t_material		*metal_alloc(t_vector3 albedo);
void			metal_free(void *metal);

#endif
