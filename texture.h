/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 19:50:18 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/21 18:18:43 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "minirt.h"

typedef struct	s_texture
{
	void		*obj;
	t_vector3	(*value)(void *obj, t_result *result);
	void		(*free)(void *obj);
}				t_texture;

#endif
