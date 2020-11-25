/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dulight.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:01:23 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/25 16:41:53 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dulight.h"

t_material		*dulight_alloc(t_texture *a)
{
	t_dulight *light;
	t_material *mat;

	light = malloc(sizeof(t_dulight));
	light->emit = a;
	mat = malloc(sizeof(t_material));
	mat->obj = light;
	mat->scatter = dulight_scatter;
	mat->emitted = dulight_emitted;
	mat->del = dulight_free;
	return (mat);
}

t_ray			dulight_scatter(void *obj, t_ray rin, t_result *result, t_vector3 *color)
{
	t_dulight *light;

	light = obj;
	result->ret = 0;
	rin.dir = *color;
	return (rin);
}

t_vector3		dulight_emitted(void *obj, double u, double v, t_vector3 p)
{
	t_dulight *light;

	light = (t_dulight*)obj;
	return (light->emit->value(light->emit->obj, u, v, p));
}

void			dulight_free(void *obj)
{
	t_dulight *light;

	light = obj;
	light->emit->free(light->emit->obj);
	free(light->emit);
	free(light);
}
