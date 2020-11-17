/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:23:41 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/17 16:02:31 by dsohn            ###   ########.fr       */
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
}				t_material;

#endif
