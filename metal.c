/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 21:16:31 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/17 22:15:12 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metal.h"

t_ray			metal_scatter(void *obj, t_ray rin, t_result *result, t_vector3 *color)
{
	t_ray scattered;
	t_metal *metal;

	metal = (t_metal*)obj;
	scattered = ray_init(result->p, vector3_reflect(vector3_norm(rin.dir), result->norm));
	*color = metal->albedo;
	result->ret = vector3_dot(scattered.dir, result->norm) > 0;
	return (scattered);
}

t_material		*metal_alloc(t_vector3 albedo)
{
	t_metal *metal;
	t_material *mat;

	metal = malloc(sizeof(t_metal));
	metal->albedo = albedo;
	mat = malloc(sizeof(t_material));
	mat->obj = metal;
	mat->scatter = metal_scatter;
	mat->del = metal_free;
	return (mat);
}

void			metal_free(void *metal)
{
	t_metal *temp;

	temp = metal;
	free(temp);
}