/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 19:50:18 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/23 20:02:29 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

#include "minirt.h"

typedef struct	s_texture
{
	void		*obj;
	t_vector3	(*value)(void *obj, double u, double v, t_vector3 point);
	void		(*free)(void *obj);
}				t_texture;

#endif
