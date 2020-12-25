/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lambertian.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 21:56:06 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/26 02:24:08 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lambertian.h"
#include "hittable.h"

t_ray			lambertian_scatter(
	void *obj, t_ray rin, t_result *result, t_vector3 *color)
{
	t_ray			scattered;
	t_lambertian	*lam;
	t_vector3		scat_dir;

	scattered = rin;
	lam = obj;
	result->ret = 1;
	scat_dir = vector3_add(result->norm, vector3_norm_random());
	if (vector3_near_zero(scat_dir))
		scat_dir = result->norm;
	scattered = ray_init(result->p, scat_dir);
	(*color) = lam->albedo->value(lam->albedo->obj, result);
	return (scattered);
}

t_material		*lambertian_alloc(t_texture *albedo)
{
	t_lambertian	*lam;
	t_material		*mat;

	lam = (t_lambertian*)malloc(sizeof(t_lambertian));
	lam->albedo = albedo;
	mat = (t_material*)malloc(sizeof(t_material));
	mat->obj = lam;
	mat->scatter = lambertian_scatter;
	mat->emitted = material_emitted;
	mat->del = lambertian_free;
	return (mat);
}

void			lambertian_free(void *lam)
{
	t_lambertian *temp;

	temp = lam;
	temp->albedo->free(temp->albedo->obj);
	free(temp->albedo);
	free(temp);
}
