/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rainbow.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 17:23:09 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/22 22:24:16 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rainbow.h"

t_vector3		rainbow_value(void *obj, t_result *result)
{
	obj = NULL;
	return (vector3_mult(
		vector3_add(result->norm, vector3_init(1, 1, 1)), 0.5));
}

void			rainbow_free(void *obj)
{
	obj = NULL;
}

t_texture		*rainbow_alloc(void)
{
	t_texture *te;

	te = (t_texture*)malloc(sizeof(t_texture));
	te->obj = NULL;
	te->value = rainbow_value;
	te->free = rainbow_free;
	return (te);
}
