/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solid_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 20:01:07 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/24 16:54:01 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solid_color.h"
#include <stdio.h>

t_texture		*solid_color_alloc(t_vector3 color)
{
	t_solid_color	*sc;
	t_texture		*result;

	sc = (t_solid_color*)malloc(sizeof(t_solid_color));
	sc->color_value = color;
	result = (t_texture*)malloc(sizeof(t_texture));
	result->obj = (void*)sc;
	result->value = solid_color_value;
	result->free = solid_color_free;
	return (result);
}

t_vector3		solid_color_value(void *obj, t_result *result)
{
	t_solid_color *sc;

	sc = (t_solid_color*)obj;
	obj = result;
	return (sc->color_value);
}

void			solid_color_free(void *obj)
{
	t_solid_color *sc;

	sc = (t_solid_color*)obj;
	free(sc);
}
