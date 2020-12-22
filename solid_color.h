/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solid_color.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 19:52:00 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/21 18:19:49 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLID_COLOR_H
# define SOLID_COLOR_H

# include "texture.h"

typedef struct	s_solid_color
{
	t_vector3	color_value;
}				t_solid_color;

t_texture		*solid_color_alloc(t_vector3 color);
t_vector3		solid_color_value(void *obj, t_result *result);
void			solid_color_free(void *obj);

#endif
