/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 19:50:18 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/19 04:45:44 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "minirt.h"

typedef struct	s_texture
{
	void		*obj;
	t_vector3	(*value)(void *obj, double u, double v, t_vector3 point);
	void		(*free)(void *obj);
}				t_texture;

#endif
