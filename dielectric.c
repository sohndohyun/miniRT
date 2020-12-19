/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dielectric.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 21:15:02 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/19 15:26:17 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dielectric.h"
#include <math.h>

static double	reflectance(double cosine, double ref_idx)
{
	double temp;

	temp = (1 - ref_idx) / (1 + ref_idx);
	temp *= temp;
	return (temp + (1 - temp) * pow(1 - cosine, 5));
}

t_ray			dielectric_scatter(
		void *obj, t_ray rin, t_result *result, t_vector3 *color)
{
	t_dielectric	*dielectric;
	t_ray			scattered;
	double			refraction_ratio;
	double			theta;

	dielectric = obj;
	refraction_ratio = result->front_face ? \
		(1.0 / dielectric->ir) : dielectric->ir;
	rin.dir = vector3_norm(rin.dir);
	result->t = fmin(vector3_dot(vector3_not(rin.dir), result->norm), 1.0);
	theta = sqrt(1.0 - result->t * result->t);
	if (refraction_ratio * theta > 1.0 ||
		reflectance(result->t, refraction_ratio) > random_double())
		scattered = ray_init(result->p, vector3_reflect(rin.dir, result->norm));
	else
		scattered = ray_init(result->p,
		vector3_refract(rin.dir, result->norm, refraction_ratio));
	*color = vector3_init(1.0, 1.0, 1.0);
	result->ret = 1;
	return (scattered);
}

t_material		*dielectric_alloc(double ir)
{
	t_dielectric	*dielectric;
	t_material		*mat;

	dielectric = malloc(sizeof(t_dielectric));
	dielectric->ir = ir;
	mat = malloc(sizeof(t_material));
	mat->obj = dielectric;
	mat->scatter = dielectric_scatter;
	mat->emitted = material_emitted;
	mat->del = dielectric_free;
	return (mat);
}

void			dielectric_free(void *dielectric)
{
	t_dielectric *temp;

	temp = dielectric;
	free(temp);
}
