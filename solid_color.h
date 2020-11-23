/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solid_color.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 19:52:00 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/23 20:02:31 by dsohn            ###   ########.fr       */
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
t_vector3		solid_color_value(void *obj, double u, double v, t_vector3 point);
void			solid_color_free(void *obj);

#endif
