/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 18:53:51 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/22 22:20:33 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disk.h"

static void		disk_get_uv(
		t_vector3 p, t_vector3 n, t_result *result, double radius)
{
	t_vector3	uv;
	t_vector3	vv;

	uv = compute_primary_dir(n);
	vv = vector3_cross(n, uv);
	result->u = (vector3_dot(uv, p) + radius) / (radius * 2);
	result->v = (vector3_dot(vv, p) + radius) / (radius * 2);
}

t_result		disk_hit(void *obj, t_ray r, double t_min, double t_max)
{
	t_disk		*disk;
	t_result	result;

	result.ret = 0;
	disk = obj;
	if (!ray_plane_t(r, ray_init(disk->orig, disk->face), &result.t))
		return (result);
	if (result.t < t_min || t_max < result.t)
		return (result);
	result.p = ray_at(r, result.t);
	if (vector3_length(vector3_sbtr(result.p, disk->orig)) > disk->radius)
		return (result);
	result_set_face_normal(&result, r, disk->face);
	disk_get_uv(vector3_sbtr(
		disk->orig, result.p), disk->face, &result, disk->radius);
	result.mat = disk->mat;
	result.ret = 1;
	return (result);
}

t_hittable		*disk_alloc(t_vector3 orig,
	t_vector3 face, double radius, t_material *mat)
{
	t_disk		*disk;
	t_hittable	*hit;

	disk = (t_disk*)malloc(sizeof(t_disk));
	disk->face = face;
	disk->orig = orig;
	disk->radius = radius;
	disk->mat = mat;
	hit = (t_hittable*)malloc(sizeof(t_hittable));
	hit->hit = disk_hit;
	hit->object = disk;
	hit->del = disk_free;
	return (hit);
}

void			disk_free(void *disk)
{
	t_disk *temp;

	temp = disk;
	temp->mat->del(temp->mat->obj);
	free(temp->mat);
	free(temp);
}
