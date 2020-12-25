/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itexture.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 02:25:28 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/26 00:52:42 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "itexture.h"

t_texture		*itexture_alloc(char *filename, void *mlx)
{
	t_itexture	*it;
	t_texture	*result;

	it = (t_itexture*)malloc(sizeof(t_itexture));
	rimage_init(&it->image, mlx, filename);
	result = malloc(sizeof(t_texture));
	result->obj = it;
	result->value = itexture_value;
	result->free = itexture_free;
	return (result);
}

t_vector3		itexture_value(void *obj, t_result *result)
{
	t_itexture *it;

	it = obj;
	return (rimage_color(&it->image, result->u, result->v));
}

void			itexture_free(void *obj)
{
	t_itexture *it;

	it = obj;
	free(it);
}
