/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 04:30:48 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/11 04:06:14 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"

typedef struct	s_fvalue
{
	double a;
	double half_b;
	double c;
	double disc;
}				t_fvalue;

static void		calculate(t_cylinder *cyl, t_ray r, t_fvalue *val)
{
	t_vector3 pp;
	t_vector3 og;
	t_vector3 op;

	pp = vector3_sbtr(r.orig, cyl->bottom);
	og = vector3_sbtr(r.dir, vector3_mult(cyl->face, vector3_dot(r.dir, cyl->face)));
	op = vector3_sbtr(pp, vector3_mult(cyl->face, vector3_dot(pp, cyl->face)));
	val->a = vector3_length_squared(og);
	val->half_b = vector3_dot(og, op);
	val->c = vector3_length_squared(op) - (cyl->radius * cyl->radius);
	val->disc = (val->half_b * val->half_b) - (val->a * val->c);
}

static double	cylinder_norm(t_cylinder *cyl, t_vector3 p, t_vector3 *n)
{
	double t;
	t_ray temp;
	t_vector3 cn;

	temp = ray_init(cyl->bottom, cyl->face);
	ray_plane_t(temp, ray_init(p, cyl->face), &t);
	cn = ray_at(temp, t);
	*n = vector3_norm(vector3_sbtr(p, cn));
	return (t);
}

static void		cylinder_get_uv(t_result *r, t_cylinder *cyl, double *u, double *v)
{
	t_vector3 p;
	double h;

	h = r->u;
	p = vector3_rotate_z(vector3_rotate_x(r->norm, 
		30.0 + vector3_angle(vector3_init(0, 1, 0), cyl->face)), 
		30.0 + - vector3_angle(vector3_init(1, 0, 0), cyl->face));
	*u = (atan2(-p.z, p.x) + PI) / (PI * 2);
	*v = h / cyl->height; 
}

t_result		cylinder_hit(void *obj, t_ray r, double t_min, double t_max)
{
	t_cylinder *cyl;
	t_result result;
	t_fvalue val;
	double sqrtd;

	result.ret = 0;
	cyl = (t_cylinder*)obj;
	calculate(cyl, r, &val);
	if (val.disc < 0)
		return (result);
	sqrtd = sqrt(val.disc);
	result.t = (-val.half_b - sqrtd) / val.a;
	result.p = ray_at(r, result.t);
	result.u = cylinder_norm(cyl, result.p, &result.norm);
	if (result.t < t_min || t_max < result.t || result.u < 0 || cyl->height < result.u)
	{
		result.t = (-val.half_b + sqrtd) / val.a;
		result.p = ray_at(r, result.t);
		result.u = cylinder_norm(cyl, result.p, &result.norm);
		if (result.t < t_min || t_max < result.t || result.u < 0 || cyl->height < result.u)
			return (result);
	}
	cylinder_get_uv(&result, cyl, &result.u, &result.v);
	result_set_face_normal(&result, r, result.norm);
	result.mat = cyl->mat;
	result.ret = 1;
	return (result);
}

t_hittable		*cylinder_alloc(t_ray r, double radius, double height, t_material *mat)
{
	t_cylinder *cyl;
	t_hittable *hit;

	cyl = malloc(sizeof(t_cylinder));
	cyl->bottom = r.orig;
	cyl->face = r.dir;
	cyl->top = ray_at(r, height);
	cyl->radius = radius;
	cyl->height = height;
	cyl->mat = mat;
	hit = malloc(sizeof(t_hittable));
	hit->hit = cylinder_hit;
	hit->object = cyl;
	hit->del = cylinder_free;
	return (hit);
}

void			cylinder_free(void *cylinder)
{
	t_cylinder *temp;

	temp = cylinder;
	temp->mat->del(temp->mat->obj);
	free(temp->mat);
	free(temp);
}
