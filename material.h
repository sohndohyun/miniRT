/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:23:41 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/25 16:40:55 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

# include "minirt.h"

typedef struct s_result t_result;

typedef struct	s_material
{
	void		*obj;
	t_ray		(*scatter)(void *obj, t_ray rin, t_result *result, t_vector3 *color);
	void		(*del)(void *obj);
	t_vector3	(*emitted)(void *obj, double u, double v, t_vector3 p);
}				t_material;

t_vector3		material_emitted(void *obj, double u, double v, t_vector3 p);

#endif
