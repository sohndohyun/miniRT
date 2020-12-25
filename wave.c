/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wave.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 15:48:47 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/24 18:33:38 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wave.h"

t_ray			wave_scatter(void *obj, t_ray rin,
	t_result *rst, t_vector3 *color)
{
	double temp;

	temp = sin(rst->u * 14 * PI);
	rst->norm = vector3_norm(vector3_add(rst->norm,
		vector3_init(0, temp, 0)));
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
