/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wave.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 15:48:47 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/26 02:53:48 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wave.h"

t_ray			wave_scatter(void *obj, t_ray rin,
	t_result *rst, t_vector3 *color)
{
	t_vector3	mynorm;

	mynorm = vector3_norm(vector3_init(0, sin(rst->u * 14 * PI), -1));
	rst->norm = vector3_norm(vector3_add(rst->norm, mynorm));
	return (lambertian_scatter(obj, rin, rst, color));
}

t_material		*wave_alloc(t_texture *albedo)
{
	t_lambertian	*lam;
	t_material		*mat;

	lam = (t_lambertian*)malloc(sizeof(t_lambertian));
	lam->albedo = albedo;
	mat = (t_material*)malloc(sizeof(t_material));
	mat->obj = lam;
	mat->scatter = wave_scatter;
	mat->emitted = material_emitted;
	mat->del = lambertian_free;
	return (mat);
}
