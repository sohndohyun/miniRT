/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 02:16:35 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/24 04:29:14 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cone.h"

static void		calculate(t_conval *val, t_cone *s, t_ray r)
{
	double		ca;
	t_vector3	co;

	ca = cos(s->angle) * cos(s->angle);
	co = vector3_sbtr(r.orig, s->cen);
	val->a = vector3_dot(r.dir, s->dir) * vector3_dot(r.dir, s->dir) - ca;
	val->b = vector3_dot(r.dir, s->dir) *
		vector3_dot(co, s->dir) - vector3_dot(r.dir, co) * ca;
	val->c = vector3_dot(co, s->dir) *
		vector3_dot(co, s->dir) - vector3_dot(co, co) * ca;
	val->disc = (val->b * val->b) - (val->a * val->c);
	if (val->disc >= 0)
		val->sqrtd = sqrt(val->disc);
}

static double	cone_norm(t_cone *s, t_vector3 p, t_vector3 *n)
{
	double		h;
	t_vector3	cp;

	cp = vector3_sbtr(p, s->cen);
	h = vector3_dot(cp, s->dir);
	*n = vector3_norm(vector3_sbtr(vector3_div(vector3_mult(cp,
		vector3_dot(s->dir, cp)), vector3_dot(cp, cp)), s->dir));
	return (h);
}

static void		calculate_result(t_result *rst, t_ray r, t_cone *cn, double t)
{
	rst->t = t;
	rst->p = ray_at(r, t);
	rst->u = cone_norm(cn, rst->p, &rst->norm);
}

static void		cone_get_uv(t_result *rst, t_cone *co, double *u, double *v)
{
	t_vector3	p;
	double		h;
	t_vector3	up;

	up = vector3_init(0, 1, 0);
	h = rst->u;
	p = vector3_aar(rst->norm, vector3_cross(co->dir, up),
		vector3_angle(co->dir, up));
	*u = (atan2(-p.z, p.x) + PI) / (PI * 2);
	*v = h / co->height;
}

t_result		cone_hit(void *obj, t_ray r, double t_min, double t_max)
{
	t_result	rst;
	t_cone		*co;
	t_conval	val;

	rst.ret = 0;
	co = (t_cone*)obj;
	calculate(&val, co, r);
	if (val.disc < 0)
		return (rst);
	calculate_result(&rst, r, co, (-val.b + val.sqrtd) / val.a);
	if (rst.t < t_min || t_max < rst.t || rst.u < 0 || co->height < rst.u)
	{
		calculate_result(&rst, r, co, (-val.b - val.sqrtd) / val.a);
		if (rst.t < t_min || t_max < rst.t || rst.u < 0 || co->height < rst.u)
			return (rst);
	}
	cone_get_uv(&rst, co, &rst.u, &rst.v);
	result_set_face_normal(&rst, r, rst.norm);
	rst.mat = co->mat;
	rst.ret = 1;
	return (rst);
}
