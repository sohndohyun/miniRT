/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dulight.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 15:28:32 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/21 18:17:55 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DULIGHT_H
# define DULIGHT_H

# include "material.h"
# include "texture.h"

typedef struct	s_dulight
{
	t_texture	*emit;
}				t_dulight;

t_material		*dulight_alloc(t_texture *a);
t_vector3		dulight_emitted(void *obj, t_result *result);
t_ray			dulight_scatter(void *obj, t_ray rin, \
			t_result *result, t_vector3 *color);
void			dulight_free(void *obj);

#endif
