/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bumpmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 02:00:20 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/26 03:02:18 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bumpmap.h"
#include "lambertian.h"
#include "solid_color.h"

t_ray			bumpmap_scatter(void *obj, t_ray rin,
	t_result *rst, t_vector3 *color)
{
	t_bumpmap	*bpm;
	t_vector3	mynorm;

	bpm = obj;
	mynorm = rimage_color(&bpm->image, rst->u, rst->v);
	rst->norm = vector3_norm(vector3_add(rst->norm, mynorm));
	return (bpm->mat->scatter(bpm->mat->obj, rin, rst, color));
}

t_material		*bumpmap_alloc(char *filename,
	t_vector3 color, void *mlx)
{
	t_bumpmap	*bpm;
	t_material	*mat;

	bpm = malloc(sizeof(t_bumpmap));
	rimage_init(&bpm->image, mlx, filename);
	bpm->mat = lambertian_alloc(solid_color_alloc(color));
	mat = malloc(sizeof(t_material));
	mat->obj = bpm;
	mat->scatter = bumpmap_scatter;
	mat->emitted = material_emitted;
	mat->del = bumpmap_free;
	return (mat);
}

void			bumpmap_free(void *obj)
{
	t_bumpmap *bpm;

	bpm = obj;
	bpm->mat->del(bpm->mat->obj);
	free(bpm->mat);
	free(bpm);
}
